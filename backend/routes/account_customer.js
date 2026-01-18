const express = require ('express');
const router = express.Router();
const account_customer = require ('../models/account_customer_model');
const validateFields = require ('../middleware/validateFields');

const required_fields = ['customer_id', 'account_id'];

router.get('/', function(request, response){
    account_customer.getAll(function(err, result){
        if(err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        else{
            response.json(result);
        }
    })
});

router.get('/:idaccount_customer', function(request, response){
    account_customer.getOne(request.params.idaccount_customer, function(err, result){
        if(err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        else{
            response.json(result);
        }
    })
});

router.post('/', validateFields(required_fields), function(request, response){
    account_customer.add(request.body, function(err, result){
        if(err){
            response.status(500).json({ status_code: response.statusCode, message: err });
        }
        else{
            response.json(result);
        }
    })
});

router.put('/:idaccount_customer', validateFields(required_fields), function(request,response){
    account_customer.update(request.body, request.params.idaccount_customer, function(err, result){
        if(err){
            response.status(500).json({status_code: response.statusCode, message: err });
        }
        else{
            response.json(result)
        }
    })
});

router.delete('/:idaccount_customer', function(request, response){
    account_customer.delete(request.params.idaccount_customer, function(err, result){
        if(err){
            response.status(500).json({status_code: response.statusCode, message: err });
        }
        else{
            response.json(result)
        }
    })
});

//router.patch()

module.exports=router;