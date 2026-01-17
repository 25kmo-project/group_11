const express = require('express');
const router = express.Router();
const card = require('../models/card_model');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const authenticateToken = require('../middleware/auth');

router.post('/', function(request,response){
    if(request.body.pin && request.body.idcard){
        const pin = request.body.pin;
        const idcard = request.body.idcard;
        card.check_pin(idcard, function(err,result){
            if (err){
                console.log("Tietokantaan ei yhteyttä");
                return response.send(err);
            }
            else {
                // Jos tietokannasta paluun pituus on enemmän kuin 0, annetulla ID:llä kortti löytyy
                if(result.length > 0) {
                    // Tarkastetaan, montako kirjautumisyritystä
                    card.getLoginAttempts(idcard, function(err, loginAttempts){
                        console.log("Kirjautumisia ennen:", loginAttempts[0].login_attempts);
                        // Jos 3 tai enemmän, palautetaan viesti "Tunnus lukittu"
                        if (loginAttempts[0].login_attempts > 2) {
                            console.log("Tunnus lukittu");
                            return response.json({"message":"Tunnus lukittu"});
                        }

                        bcrypt.compare(pin, result[0].pin, function(err, compareResult){
                            // HUOM! Jotta sovellus ei kaadu tähän, on .env-tiedostossa oltava MY_TOKEN sijoitettuna
                            const token = generateAccessToken(idcard);
                            console.log("Token:", token);
                            if(compareResult){
                                // Resetoidaan kirjautmiset onnistuneen kirjautumisen yhteydessä
                                card.resetLoginAmount(idcard, function(err, response){
                                    if (err) {
                                        console.log("Virhe kirjautumisyritysten resetoinnissa");
                                        response.send(err);
                                    } else {
                                        console.log("Kirjautumismäärä resetoitu kortille:", idcard);
                                    }
                                });
                                response.setHeader('Content-Type', 'application/json');
                                response.json({
                                    success: true,
                                    message: "Login OK",
                                    idcard: idcard,
                                    token: token
                                });
                            }
                            // Päivitetään uusi kirjautumisten lukumäärä epäonnistuneessa kirjautumisessa
                            else{
                                console.log("PIN ei täsmää");
                                console.log("Kirjautumisia jälkeen:", loginAttempts[0].login_attempts + 1);
                                card.updateLoginAmount(idcard);
                                return response.json({"message":"Idcard ja PIN eivät täsmää"});
                            }
                        });
                    });
                }
                // Tietokannan paluun pituus == 0 -> ID:llä ei korttia
                else {
                    console.log("ID:llä ei ole korttia");
                    return response.json({"message":"Idcard ja PIN eivät täsmää"});
                }
            }
        });
    }
    // Joko idcard tai PIN uupuu syötteestä
    else {
        console.log("Idcard tai PIN puuttuu");
        return response.json({"message":"Idcard ja PIN eivät täsmää"});
    }
});

function generateAccessToken(idcard) {
    return jwt.sign({idcard}, process.env.MY_TOKEN, {expiresIn: '1800s'});
}

module.exports=router;