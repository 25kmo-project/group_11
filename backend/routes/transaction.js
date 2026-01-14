const express = require("express");
const router = express.Router();
const transaction = require('../models/transaction_model');
const  validateFields = require('../middleware/validateFields');

const requirered_fields = ['idaccount', 'amount', 'transaction_type', 'timestamp'];

router.get('/:idaccount', function(request, response){
    transaction.getAllUser(request.params.idaccount, function(err, result){
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        else if (result.length === 0) {
            return response.status(404).json({ status_code: response.statusCode, message: 'User not found.' })
        }
        response.json(result);

    })
});

router.get('/transaction/:idtransaction', function(request, response){
    transaction.getOne(request.params.idtransaction, function(err, result){
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        else if (result.length === 0) {
            return response.status(404).json({ status_code: response.statusCode, message: 'Transaction not found.' })
        }
        response.json(result);
    })
});

router.post('/', validateFields(requirered_fields), function(request,response){
    transaction.create(request.body, function(err,result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        response.json(result);
    })
});

router.put('/:idtransaction', validateFields(requirered_fields), function(request,response){
    transaction.update(request.body, request.params.idtransaction, function(err, result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'User not found.' })
        }

    response.json(result);    
  })
});

router.patch('/:idtransaction', function(request,response){
    transaction.update(request.body, request.params.idtransaction, function(err, result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'User not found.' })
        }

    response.json(result);    
  })
});

router.delete('/:idtransaction', function(request,response){
    transaction.delete(request.params.idtransaction, function(err, result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'Transaction not found.' })
        }
        response.json(result);
    })
});

module.exports = router;