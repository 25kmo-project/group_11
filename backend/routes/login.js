const express = require('express');
const router = express.Router();
const card = require('../models/card_model');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

router.post('/:idcard/reset', function(request,response) {
    card.resetLoginAmount(request.params.idcard, function(err, result){
        if (err) {
            return response.sendStatus(500);
        }
        else {
            return response.json({
                success: true,
                message: "Login attemts reset",
                idcard: request.params.idcard});
        }
    });
});

router.post('/', function (request, response) {
    if (request.body.pin && request.body.idcard) {
        const pin = request.body.pin;
        const idcard = request.body.idcard;
        card.getOne(idcard, function (err, result) {
            if (err) {
                console.log("Tietokantaan ei yhteyttä");
                return response.sendStatus(500);
            } else {
                // Jos tietokannasta paluun pituus on enemmän kuin 0, annetulla ID:llä kortti löytyy
                if (result.length > 0) {
                    const dbPin = result[0].pin;
                    const login_attempts = result[0].login_attempts;
                    console.log("Aiemmat kirjautumiset:", login_attempts);

                    // Jos 3 tai enemmän, palautetaan viesti "Tunnus lukittu"
                    if (login_attempts > 2) {
                        console.log("Tunnus lukittu");
                        return response.json({ message: "Tunnus lukittu" });
                    }
                
                    bcrypt.compare(pin, dbPin, function (err, compareResult) {
                        if (err) {
                            return response.sendStatus(500);
                        }
                    
                        if (compareResult) {
                            // HUOM! Jotta sovellus ei kaadu tähän, on .env-tiedostossa oltava MY_TOKEN sijoitettuna
                            const token = generateAccessToken(idcard);
                        
                            // Resetoidaan kirjautmiset onnistuneen kirjautumisen yhteydessä
                            card.resetLoginAmount(idcard);
                            console.log("Kirjautumismäärä resetoitu kortille:", idcard);
                        
                            // Palautetaan onnistuneessa kirjautumisessa alla olevat tiedot
                            return response.json({
                                success: true,
                                message: "Login OK",
                                idcard: idcard,
                                token: token
                            });
                        } else {
                            // Päivitetään uusi kirjautumisten lukumäärä epäonnistuneessa kirjautumisessa
                            console.log("PIN ei täsmää");
                            console.log("Kirjautumisyrityksiä:", login_attempts + 1);
                            card.addOneLogin(idcard);
                            return response.json({ message: "Idcard ja PIN eivät täsmää" });
                        }
                    });
                }
            // Tietokannan paluun pituus == 0 -> ID:llä ei korttia
                else {
                  console.log("ID:llä ei ole korttia");
                  return response.json({ message: "Idcard ja PIN eivät täsmää" });
                }
            }
        });
    }
    // Joko idcard tai PIN uupuu syötteestä
    else {
        console.log("Idcard tai PIN puuttuu");
        return response.json({ message: "Idcard ja PIN eivät täsmää" });
    }
});


function generateAccessToken(idcard) {
    return jwt.sign({idcard}, process.env.MY_TOKEN, {expiresIn: '1800s'});
}


module.exports=router;