const { response } = require('../app');
const card = require('../models/card_model');
const account = require('../models/account_model');

const cardContoller = {
    // Funktiolla tarkastetaan, voiko annetun tilin lisätä kortille
    // Funktio tekee seuraavat tarkastukset
    // Onko kortti olemassa
    // Onko tili olemassa
    // Onko kortilla tilejä entuudestaan
    // Vertaa mahdollisesti olemasa olevaa ja lisättävää
    // Mikäli ei mitään esteitä, tili listään kortille
    // Ehtona maksimissaan yksi DEBIT- sekä CREDIT-tyyppinen tili
    authAccountAdd: function(request, response) {
        const idcard = request.body.idcard;
        const idAccountToAdd = request.body.idaccount;

        // Tarkistetaan kortin olemassaolo
        card.getOne(idcard, function(err, result) {
            if (err) {
                return response.send(err)
            }
            if (result.length === 0) {
                return response.json({message:"Antamaasi korttia ei olemassa"});
            }

            // Tarkistetaan tilin olemassaolo
            account.getOne(idAccountToAdd, function(err, result) {
                if (err) {
                    return response.send(err);
                }
                if(result.length === 0) {
                    return response.json({message:"Antamaasi tilia ei olemassa"});
                }

                // Tarkistetaan kortin nykyiset tilit
                card.getCardAccounts(idcard, function(err, accounts) {
                    if (err) {
                        console.log('Tietokantavirhe:', err);
                        return response.status(500).json(err);
                    }

                    if (accounts.length === 0) {
                        card.addAccountToCard(idcard,idAccountToAdd);
                        return response.json({message: "Tili lisatty onnistuneesti"})
                    }

                    if (accounts.length === 1) {
                        const accountid = accounts[0].account_id;

                        // Tarkistetaan olemassa olevan tilin tyyppi
                        card.checkAccountType(accountid, function(err, accountType) {
                            if (err) {
                                return response.send(err);
                            }

                            const existAccountType = accountType[0].account_type;
                            console.log("Olemassa:", existAccountType);

                            // Tarkistetaan lisättävän tilin tyyppi
                            card.checkAccountType(idAccountToAdd, function(err, accountType2) {
                                if (err) {
                                    return response.send(err);
                                }

                                const addingAccountType = accountType2[0].account_type;
                                console.log("Lisattava:", addingAccountType);

                                // Vertailu, onko lisättävä samanlainen kuin jo olemassa oleva
                                if (existAccountType === addingAccountType) {
                                    return response.json({message: "Kortilla on jo lisattavan tyypin tili"})
                                }
                                else {
                                    card.addAccountToCard(idcard,idAccountToAdd);
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
};

module.exports = cardContoller;