const { response } = require('../app');
const card = require('../models/card_model');

const cardContoller = {
    authAccountAdd: function(request, response) {
        const idcard = request.body.idcard;
        const idAccountToAdd = request.body.idaccount;

        // Tarkistetaan kortin olemassaolo
        card.checkCardExist(idcard, function(err, result) {
            if (err) {
                response.send(err)
            }
            if (result.length === 0) {
                return response.json({message:"Korttia ei olemassa"});
            }

            // Tarkistetaan tilin olemassaolo
            card.checkAccountExist(idAccountToAdd, function(err, result) {
                if (err) {
                    response.send(err);
                }
                if(result.length === 0) {
                    return response.json({message:"Tiliä ei olemassa"});
                }

                // Tarkistetaan kortin nykyiset tilit
                card.getCardAccounts(idcard, function(err, accounts) {
                    if (err) {
                        console.log('Tietokantavirhe:', err);
                        return response.status(500).json(err);
                    }

                    if (accounts.length === 0) {
                        card.addAccountToCard(idcard,idAccountToAdd);
                        return response.json({message: "Tili lisätty onnistuneesti"})
                    }

                    if (accounts.length === 1) {
                        const accountid = accounts[0].account_id;

                        // Tarkistetaan olemassa olevan tilin tyyppi
                        card.checkAccountType(accountid, function(err, accountType) {
                            if (err) {
                                return response.send(err);
                            }

                            const existAccountType = accountType[0].account_type;
                            console.log("Olemassa oleva:", existAccountType);

                            // Tarkistetaan lisättävän tilin tyyppi
                            card.checkAccountType(idAccountToAdd, function(err, accountType2) {
                                if (err) {
                                    return response.send(err);
                                }

                                const addingAccountType = accountType2[0].account_type;
                                console.log("Lisättävä:", addingAccountType);

                                // Vertailu, onko lisättävä samanlainen kuin jo olemassa oleva
                                if (existAccountType === addingAccountType) {
                                    return response.json({message: "Kortilla on jo lisattavan tyypin tili"})
                                }
                                else {
                                    card.addAccountToCard(idcard,idAccountToAdd);
                                    return response.json({message: "Tili lisätty onnistuneesti"})
                                }
                            });
                        });
                    }
                    else {
                        return response.json({ message: "Kortilla on jo DEBIT ja CREDIT" });
                    }
                });
            });
        }); 
    }
};

module.exports = cardContoller;