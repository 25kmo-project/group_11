const { response } = require('../app');
const card = require('../models/card_model');
const account = require('../models/account_model');
const card_account = require('../models/card_account_model');

const cardContoller = {


        
        



            
            





                        
                        




    accountRemove:function(request, response){
        const idcard = request.body.card_id;
        const idAccountToRemove = request.body.account_id;
        console.log("idcard:", idcard);
        console.log("idAccountToRemove:", idAccountToRemove);
        
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
            account.getOne(idAccountToRemove, function(err, result) {
                if (err) {
                    return response.status(500).json(err);
                }
                if(result.length === 0) {
                    return response.json({message:"Antamaasi tilia ei olemassa"});
                }
                // Haetaan kortin nykyiset tilit
                card_account.getCardAccounts(idcard, function(err, accounts) {
                    if (err) {
                        return response.status(500).json(err);
                    }

                    if (accounts.length === 0) {
                        return response.json({"message":"Annetulla kortilla ei ole tilejä"})
                    }
                    console.log(accounts);

                    for (const account of accounts) {
                        console.log(account);
                        if (account.account_id == idAccountToRemove) {
                            const idcard_account = account.idcard_account;
                            card_account.deleteAccountFromCard(idAccountToRemove, function(err, result){
                                if(err) {
                                    return response.send(err);
                                }
                                else{
                                    
                                    return response.json ({
                                        success: true,
                                        message: "Delete ok",
                                        idcard: idcard,
                                        deletedAccount: idAccountToRemove
                                    })
                                }
                            })
                        }
                    }
                    return response.json({"message":"testi"});
                });
            }); 
        });
    },
}

module.exports = cardContoller;