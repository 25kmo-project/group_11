const express = require ('express');
const router = express.Router();
const customer = require('../models/customer_model');

router.get('/', function(request, response){
    customer.getAll(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log("tiedonhaku onnistui");
            response.json(result);
        }
    })
});

router.get('/:idcustomer', function(request, response){
    customer.getOne(request.params.idcustomer, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log("tiedonhaku onnistui");            
            response.json(result[0]);
        }

    })
});
router.post('/', function(request, response){
    customer.add(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result[0]);
            console.log("lisäys onnistui");
        }
    })
});
router.put('/:idcustomer', function(request, response){
    customer.update(request.body, request.params.idcustomer, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result[0])
            console.log("päivitys onnistui");
        }
    })
});

router.delete('/:idcustomer', function(request, response){
    customer.delete(request.params.idcustomer, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result[0]);
            console.log("Käyttäjä", request.params.idcustomer, "poistettu");
        }
    })
});

module.exports=router;