const express = require("express");
const router = express.Router();
const card = require('../models/card_model');
const card_account = require('../models/card_account_model');
const account = require("../models/account_model");

router.get('/',function(request, response){
    card.getAll(function(err,result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/:idcard',function(request, response){
    card.getOne(request.params.idcard, function(err,result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.post('/',function(request,response){
    card.add(request.body, function(err,result){
        if (err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.put('/:idcard', function(request,response){
    card.update(request.body, request.params.idcard, function(err, result){
        if (err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.delete('/:idcard', function(request,response){
    card.delete(request.params.idcard, function(err, result){
        if (err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.get('/:idcard/accounts', function(request, response){
    const idcard = request.params.idcard;
    // Haetaan kortti ja tarkistetaan sen olemassa olo
    card.getOne(idcard, function(err, result) {
        if (err) {
            return response.status(500).json(err);
        }
        if (result.length === 0) {
            return response.status(404).json({ message: "Antamaasi korttia ei ole olemassa" });
        }
        // Haetaan kortilla olevat tilit
        card_account.getCardAccounts(idcard, function(err, result){
            if (err){
                return response.status(500).json(err);
            }
            // Jos ei tilejä
            if (result.length === 0) {
                return response.json({message: "Kortilla ei tilejä"});
            }
            let accounts = [];
            let count = 0;

            // Käydään tilit läpi ja tallennetaan taulukkoon
            for (const card_account of result) {
                const idaccount = card_account.account_id;
                account.getOne(idaccount, function(err, accountResult){
                    if(err) {
                        return response.status(500).json(err);
                    }

                    // Tilistä json-muotoinen objekti
                    let foundAccount = {
                        idaccount: accountResult[0].idaccount,
                        balance: accountResult[0].balance,
                        account_type: accountResult[0].account_type,
                        credit_limit: accountResult[0].credit_limit,
                        idowner: accountResult[0].idowner
                    }

                    // Tallennetaan tili kerrallaan taulukkoon
                    accounts.push(foundAccount);
                    count++;

                    // Kunnes tilit käyty läpi, palautetaan ne
                    if (count === result.length) {
                        console.log(accounts);
                        return response.json(accounts);
                    }
                });
            }
        });
    });
});

module.exports = router;
