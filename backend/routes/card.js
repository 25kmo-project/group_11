const express = require("express");
const router = express.Router();
const card = require('../models/card_model');
const cardContoller = require('../controllers/card_controller');

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
    card.getAll(function(err,result){
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

router.post('/accounttocard', function(request,response){
    //Functio check does card have a debit or credit account
    cardContoller.authAccountAdd(request, response)
});


module.exports = router;
