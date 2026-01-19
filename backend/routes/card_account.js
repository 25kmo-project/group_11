const express = require("express");
const router = express.Router();
const account = require('../models/account_model');
const card = require('../models/card_model');
const card_account = require('../models/card_account_model');

router.post('/accounttocard', function(request,response){
    const idcard = request.body.idcard;
    const idAccountToAdd = request.body.idaccount;

    // Tarkistetaan että parametrit on annettu
    if (!idcard) {
        return response.status(400).json({ message: "idcard puuttuu" });
    }

    if (!idAccountToAdd) {
        return response.status(400).json({ message: "idaccount puuttuu" });
    }

    // Tarkistetaan kortin olemassaolo
    card.getOne(idcard, function(err, result) {
        if (err) {
            console.log('Tietokantavirhe:', err);
            return response.status(500).json(err);
        }
        if (result.length === 0) {
            return response.status(404).json({ message: "Antamaasi korttia ei ole olemassa" });
        }
        
        // Tarkistetaan tilin olemassaolo
        account.getOne(idAccountToAdd, function(err, result) {
            if (err) {
                return response.status(500).json(err);
            }

            if(result.length === 0) {
                return response.json({message:"Antamaasi tilia ei olemassa"});
            }

            const addingAccountType = result[0].account_type;

            // Tarkistetaan kortin nykyiset tilit
            card_account.getCardAccounts(idcard, function(err, accounts) {
                if (err) {
                    return response.status(500).json(err);
                }

                // Kortilla ei ole vielä tilejä
                if (accounts.length === 0) {
                    card_account.addAccountToCard(idcard,idAccountToAdd);
                    return response.json({message: "Tili lisatty onnistuneesti"})
                }

                // Kortilla on jo kaksi tiliä
                if (accounts.length > 1) {
                    return response.json({ message: "Kortilla on jo DEBIT ja CREDIT tilit" });
                }

                // Kortilla on yksi tili -> tarkistetaan tyyppi
                const accountid = accounts[0].account_id;

                account.getOne(accountid, function(err, result) {
                    if (err) {
                        return response.status(500).json(err);
                    }

                    const existAccountType = result[0].account_type;

                    // Verrataan tilien tyyppejä
                    if (existAccountType === addingAccountType) {
                        return response.json({ message: "Kortilla on jo lisättävän tyypin tili" });
                    }
                    else {
                        card_account.addAccountToCard(idcard, idAccountToAdd);
                        return response.json({ message: "Tili lisätty onnistuneesti" });
                    }
                });
            });
        });
    });
});

router.delete('/removeaccountfromcard', function (request, response) {
    const idcard = request.body.card_id;
    const idAccountToRemove = request.body.account_id;

    // Tarkistetaan kortin olemassaolo
    card.getOne(idcard, function (err, result) {
        if (err) {
            console.log('Tietokantavirhe:', err);
            return response.status(500).json(err);
        }

        if (result.length === 0) {
            return response.status(404).json({ message: "Antamaasi korttia ei olemassa" });
        }

        // Tarkistetaan tilin olemassaolo
        account.getOne(idAccountToRemove, function (err, result) {
            if (err) {
                return response.status(500).json(err);
            }

            if (result.length === 0) {
                return response.status(404).json({ message: "Antamaasi tilia ei olemassa" });
            }


            // Haetaan kortin nykyiset tilit
            card_account.getCardAccounts(idcard, function (err, accounts) {
                if (err) {
                    return response.status(500).json(err);
                }

                if (accounts.length === 0) {
                    return response.status(400).json({ message: "Annetulla kortilla ei ole tilejä" }); 
                }

                // Käydään tilit läpi, vastaako poistettava kortilla olevia
                for (const account of accounts) {
                    if (account.account_id == idAccountToRemove) {

                        const idcard_account = account.idcard_account;
                        // Poistetaan annettu tili kortilta, jos sellainen löyty
                        return card_account.deleteAccountFromCard(idcard_account, function(err, result){
                            if (err) {
                                return response.status(500).json(err);
                            } else {
                                console.log("testi3");
                                return response.json({
                                    success: true,
                                    message: "Delete ok",
                                    idcard: idcard,
                                    deletedAccount: idAccountToRemove
                                })
                            }
                        });
                    }
                }
                // Jos kortilla ei ole kyseistä tiliä
                return response.status(404).json({ message: "Annetulla kortilla ei ole kyseistä tiliä" });
            });
        });
    });
});



module.exports = router;