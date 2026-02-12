const express = require("express");
const router = express.Router();
const account = require('../models/account_model');
const card = require('../models/card_model');
const card_account = require('../models/card_account_model');
const validateFields = require('../middleware/validateFields');

const required_fields = ['idcard', 'idaccount']

router.get('/', function(request, response){
    card_account.getAll(function(err,result){
        if(err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }

        response.json(result);
    });
});

router.get('/:idcardaccount', function(request, response){
    card_account.getOne(request.params.idcardaccount, function(err, result){
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }

        response.json(result);
    });
});

router.put('/accounttocard/:id', function(request, response) {
    const idCardAccount = request.params.id;
    const idCard = request.body.idcard;
    const idAccount = request.body.idaccount;

    // Tarkistetaan, löytyykö kortti-tili yhteys
    card_account.getOne(idCardAccount, function(err, result){
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        if (result.length === 0) {
            return response.status(404).json({message: "Card-account relation not found."});
        }

        // Kutsutaan validointi funktiota
        validateCardAccountLink(idCard, idAccount, idCardAccount, function(err) {
            if (err) {
                return response.status(500).json({ status_code: response.statusCode, message: err });
            }

            card_account.update(idCardAccount, idAccount, idCard, function(err){
                if (err){
                    return response.status(500).json({status_code: response.statusCode, message: err});
                }
                
                // Jos kaikki menee läpi, palautetaan viesti onnistuneesta päivittämisestä
                return response.json({message: "Tili päivitetty onnistuneesti."});
            });
        });
    });
});

router.post('/accounttocard', validateFields(required_fields), function(request,response){
    const idCard = request.body.idcard;
    const idAccount = request.body.idaccount;

    // Kutsutaan validointi funktiota
    validateCardAccountLink(idCard, idAccount, null, function(err){
        if (err) {
            console.log('Tietokantavirhe:', err);
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }

        // Jos kaikki menee läpi, palautetaan viesti onnistuneesta lisäämisestä
        card_account.addAccountToCard(idCard, idAccount, function() {
            return response.json({message: "Tili lisatty onnistuneesti."});
        });
    });
});

router.delete('/removeaccountfromcard', validateFields(required_fields), function (request, response) {
    const idcard = request.body.idcard;
    const idAccountToRemove = request.body.idaccount;

    // Tarkistetaan kortin olemassaolo
    card.getOne(idcard, function (err, result) {
        if (err) {
            console.log('Tietokantavirhe:', err);
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.length === 0) {
            return response.status(404).json({ message: "Antamaasi korttia ei olemassa. " });
        }

        // Tarkistetaan tilin olemassaolo
        account.getOne(idAccountToRemove, function (err, result) {
            if (err) {
                return response.status(500).json({ status_code: response.statusCode, message: err });
            } else if (result.length === 0) {
                return response.status(404).json({ message: "Antamaasi tilia ei olemassa. " });
            }


            // Haetaan kortin nykyiset tilit
            card_account.getCardAccounts(idcard, function (err, accounts) {
                if (err) {
                    return response.status(500).json({ status_code: response.statusCode, message: err });
                } else if (accounts.length === 0) {
                    return response.status(400).json({ message: "Annetulla kortilla ei ole tilejä." }); 
                }

                // Käydään tilit läpi, vastaako poistettava kortilla olevia
                for (const account of accounts) {
                    if (account.account_id == idAccountToRemove) {

                        const idcard_account = account.idcard_account;
                        // Poistetaan annettu tili kortilta, jos sellainen löyty
                        return card_account.deleteAccountFromCard(idcard_account, function(err, result){
                            if (err) {
                                return response.status(500).json({ status_code: response.statusCode, message: err });
                            } else {
                                return response.json({
                                    success: true,
                                    message: "Tilin ja kortin liitos poistettu.",
                                    idcard: idcard,
                                    deletedAccount: idAccountToRemove
                                })
                            }
                        });
                    }
                }
                // Jos kortilla ei ole kyseistä tiliä
                return response.status(404).json({ message: "Annetulla kortilla ei ole kyseistä tiliä." });
            });
        });
    });
});

function validateCardAccountLink(idCard, idAccountToAdd, excludeCardAccountId = null, callback){
    // Haetaan kortin tiedot
    card.getOne(idCard, function(err, cardResult){
        if (err) {
            console.log('Tietokantavirhe:', err);
            return callback({ status: 500, message: err });
        }
        // Jos paluuarvon pituus = 0 -> Korttia ei olemassa
        if (cardResult.length === 0) {
            return callback({ status: 404, message: "Antamaasi korttia ei ole olemassa." });
        }
        // Haetaan lisättävän tilin tiedot
        account.getOne(idAccountToAdd, function(err, accountResult){
            if (err) {
                console.log('Tietokantavirhe:', err);
                return callback({ status: 500, message: err });
            }
            // Jos paluuarvon pituus = -> Lisättävää tiliä ei olemassa
            if (accountResult.length === 0) {
                return callback({ status: 404, message: "Antamaasi tiliä ei ole olemassa." });
            }
            // Tallennetaan lisättävän tilin tyyppi
            const addingAccountType = accountResult[0].account_type;

            // Haetaan kortilla olevat tilit
            card_account.getCardAccounts(idCard, function(err, accounts){
                if (err) {
                    console.log('Tietokantavirhe:', err);
                    return callback({ status: 500, message: err });
                }

                // Tallennetaan olemassa olevien tilien ID:t 
                if (excludeCardAccountId) {
                    let filteredAccounts = [];
                    for (let i = 0; i < accounts.length; i++) {
                        if (accounts[i].id !== excludeCardAccountId) {
                            filteredAccounts.push(accounts[i]);
                        }
                    }
                    accounts = filteredAccounts;
                }

                // Jos accounts-taulun pituus = 0 -> Kortille ei kohdistu tilejä
                if (accounts.length === 0) {
                    return callback(null);
                }

                // Jos paluuarvon pituus yli 1 -> Kortilla on jo DEBIT ja CREDIT
                if (accounts.length > 1) {
                    return callback({ status: 409, message: "Kortilla on jo DEBIT ja CREDIT tilit." });
                }

                // Tallennetaan olemassa olevan tilin id
                const existingAccountId = accounts[0].account_id;

                // Haetaan olemassa olevan tilin tiedot
                account.getOne(existingAccountId, function(err, result){
                    if (err) {
                        console.log('Tietokantavirhe:', err);
                        return callback({ status: 500, message: err });
                    }

                    // Tallennetaan olemassa olevan tilin tyyppi
                    const existType = result[0].account_type;

                    // Jos lisättävä tili on saman tyyppinen kuin olemassa olevaa
                    if (existType === addingAccountType) {
                        return callback({ status: 409, message: "Kortilla on jo lisättävän tyypin tili." });
                    }

                    // Jos tarkastukset menee läpi, saa lisäys/muutos jatkua
                    callback(null);
                });
            });
        });
    });
}


module.exports = router;