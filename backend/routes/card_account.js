const express = require("express");
const router = express.Router();
const card = require('../models/card_model');
const cardContoller = require('../controllers/card_controller');

router.post('/accounttocard', function(request,response){
    //Function check does card have a debit or credit account
    const idcard = request.body.idcard;
    const idAccountToAdd = request.body.idaccount;
    // Tarkistetaan kortin olemassaolo
    card.getOne(idcard, function(err, result) {
        if (err) {
            console.log('Tietokantavirhe:', err);
            return response.status(500).json(err);
        }
        if (result.length === 0) {
            return response.json({message:"Antamaasi korttia ei olemassa"});
        }
        
        // Tarkistetaan tilin olemassaolo
        account.getOne(idAccountToAdd, function(err, result) {
            if (err) {
                return response.status(500).json(err);
            }
            if(result.length === 0) {
                return response.json({message:"Antamaasi tilia ei olemassa"});
            }
            // Tarkistetaan kortin nykyiset tilit
            card_account.getCardAccounts(idcard, function(err, accounts) {
                if (err) {
                    return response.status(500).json(err);
                }

                if (accounts.length === 0) {
                    card_account.addAccountToCard(idcard,idAccountToAdd);
                    return response.json({message: "Tili lisatty onnistuneesti"})
                }
                // Tarkistetaan olemassa olevan tilin tyyppi
                if (accounts.length === 1) {
                    const accountid = accounts[0].account_id;
                    account.getOne(accountid, function(err, accountType) {
                        if (err) {
                            return response.status(500).json(err);
                        }
                    
                        const existAccountType = accountType[0].account_type;
                        console.log("Olemassa:", existAccountType);
                    
                        // Tarkistetaan lisättävän tilin tyyppi
                        account.getOne(idAccountToAdd, function(err, accountType2) {
                            if (err) {
                                return response.status(500).json(err);
                            }
                        
                            const addingAccountType = accountType2[0].account_type;
                            console.log("Lisattava:", addingAccountType);
                        
                            // Vertailu, onko lisättävä samanlainen kuin jo olemassa oleva
                            if (existAccountType === addingAccountType) {
                                return response.json({message: "Kortilla on jo lisattavan tyypin tili"})
                            }
                            else {
                                card_account.addAccountToCard(idcard,idAccountToAdd);
                                return response.json({message: "Tili lisatty onnistuneesti"})
                                }
                            });
                        });
                    }
                    else {
                        return response.json({ message: "Kortilla on jo DEBIT ja CREDIT tilit" });
                    }
                });
            });
        }); 
    },
);

router.delete('/removeaccountfromcard', function(request, response){
    //Controller check does card have rights to given account
    cardContoller.accountRemove(request,response)
});


module.exports = router;