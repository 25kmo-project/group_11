const express = require("express");
const router = express.Router();
const transaction = require('../models/transaction_model');
const validateFields = require('../middleware/validateFields');

const required_fields = ['idtransaction', 'idaccount', 'amount', 'date', 'description'];
const post_required_fields = ['idaccount', 'amount', 'date', 'description'];

router.get('/account/:idaccount', function(request, response){
    const idaccount = request.params.idaccount;

    const limit = parseInt(request.query.limit) || 10;
    const page = parseInt(request.query.page) || 1;

    const safeLimit = limit > 0 ? limit : 10;
    const safePage = page > 0 ? page : 1;

    const offset = (safePage - 1) * safeLimit;

    transaction.getAccountTransactions(
        idaccount,
        safeLimit,
        offset,
        function(err, result){
            if (err) {
                return response.status(500).json({
                    status_code: response.statusCode,
                    message: err
                });
            }

            response.json({
                page: safePage,
                limit: safeLimit,
                data: result
            });
        }
    );
});

router.get('/:idtransaction', function(request, response){
    transaction.getOne(request.params.idtransaction, function(err, result){
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.length === 0) {
            return response.status(404).json({ status_code: response.statusCode, message: 'Tilitapahtumaa ei löytynyt.' })
        }
        
        response.json(result);
    })
});

router.get('/account/all/:idaccount', function(request, response) {
    const idaccount = request.params.idaccount;
    transaction.getAllAccountTransactions(idaccount, function(err, result) {
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }

        response.json(result);
    });
});

router.post('/', validateFields(post_required_fields), function(request,response){
    transaction.add(request.body, function(err,result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }

        response.json(result);
    })
});

router.put('/:idtransaction', validateFields(required_fields), function(request,response){
    transaction.update(request.body, request.params.idtransaction, function(err, result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'Tilitapahtumaa ei löytynyt.' })
        }

        response.json(result);    
  })
});

router.patch('/:idtransaction', function(request,response){
    transaction.update(request.body, request.params.idtransaction, function(err, result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'Tilitapahtumaa ei löytynyt.' })
        }

        response.json(result);    
  })
});

router.delete('/:idtransaction', function(request,response){
    transaction.delete(request.params.idtransaction, function(err, result){
        if (err){
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'Tilitapahtumaa ei löytynyt.' })
        }

        response.json(result);
    })
});

module.exports = router;