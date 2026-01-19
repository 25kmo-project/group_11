const express = require("express");
const router = express.Router();
const card = require('../models/card_model');

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

module.exports = router;
