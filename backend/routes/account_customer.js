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
    response.json(result);
    })
});

router.get('/:idaccount_customer', function(request, response){
    account_customer.getOne(request.params.idaccount_customer, function(err, result){
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }

        if (result.length === 0) {
            return response.status(404).json({ status_code: response.statusCode, message: 'User not found.' });
        }

    response.json(result);
    })
});

router.post('/', validateFields(required_fields), function(request, response){
    account_customer.add(request.body, function(err, result){
        if (err) {
            error_message = err;
        if (err.errno === 1062) {
            error_message = 'Cannot create an account with the same ID as an existing account.';
        } else if (err.errno === 1452) {
            error_message = 'Customer ID ' + request.body.idowner.toString() + ' does not exist.';
        }
        return response.status(500).json({ status_code: response.statusCode, message: error_message }); 
        }
    response.json(result);
    })
});

router.put('/:idaccount_customer', validateFields(required_fields), function(request,response){
    account_customer.update(request.body, request.params.idaccount_customer, function(err, result){
        if(err){
            return response.status(500).json({status_code: response.statusCode, message: err });
        }
        if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'User not found.' });
        }
    response.json(result);
    })
});

router.patch('/:idaccount_customer', function(request, response){
    account_customer.update(request.body, request.params.idaccount_customer, function(err, result){
        if(err){
            return response.status(500).json({status_code: response.statusCode, message: err });
        }
        if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'User not found.' });
        }
    response.json(result);
    })
});

router.delete('/:idaccount_customer', function(request, response){
    account_customer.delete(request.params.idaccount_customer, function(err, result){
        if(err){
            return response.status(500).json({status_code: response.statusCode, message: err });
        }
        if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'User not found.' })
        }
    response.json(result);
    })
});

router.get('/accountdata/:idaccount', function(request, response){
    account_customer.accountData(request.params.idaccount, function(err, result){
        if(err){
            return response.status(500).json({status_code: response.statusCode, message: err });
        }
        if (result[0].length === 0) {
            return response.status(404).json({ status_code: response.statusCode, message: 'User not found.' });
        }
    response.json(result[0]);
    })
});

router.get('/customerdata/:idcustomer', function(request, response){
    const idcustomer = parseInt(request.params.idcustomer);
    account_customer.customerData(idcustomer, function(err, result){
        if(err){
            return response.status(500).json({status_code: response.statusCode, message: err });
        }
        if (result[0].length === 0) {
            return response.status(404).json({ status_code: response.statusCode, message: 'User not found.' });
        }
    response.json(result[0]);
    })
});

module.exports=router;