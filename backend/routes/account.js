var express = require('express');
var router = express.Router();
var account = require('../models/account_model');
var validateFields = require('../middleware/validateFields');

const required_fields = ['idaccount', 'balance', 'account_type', 'credit_limit', 'idowner']

/* GET accounts listing. */
router.get('/', function(request, response) {
    account.getAll(function(err, result) {
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        
        response.json(result);
    })
});

router.get('/:idaccount', function(request, response) {
    account.getOne(request.params.idaccount, function(err, result) {
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        }
        
        response.json(result);
    })
});

// Field validation is performed to return more verbose errors for API caller
router.post('/', validateFields(required_fields), function(request, response) {
    account.add(request.body, function(err, result) {
        if (err) {
            var error_message = err;
            var status_code = 500;
            if (err.errno === 1062) {
                status_code = 400;
                error_message = 'Ei voi luoda tiliä samalla tili ID:llä kuin toinen tili.';
            } else if (err.errno === 1452) {
                status_code = 404; 
                error_message = 'Asiakas ID:llä ' + request.body.idowner.toString() + ' ei ole olemassa.';
            }
            return response.status(status_code).json({ status_code: response.statusCode, message: error_message }); 
        }
        
        response.json(result);
    })
});

// Field validation is performed to return more verbose errors for API caller
router.put('/:idaccount', validateFields(required_fields), function(request, response) {
    account.update(request.body, request.params.idaccount, function(err, result) {
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'Tiliä ei löytynyt.' })
        }
        
        response.json(result);    
    })
});

router.patch('/:idaccount', function(request, response) {
    account.update(request.body, request.params.idaccount, function(err, result) {
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'Tiliä ei löytynyt.' })
        }
        
        response.json(result);
    })
});

router.delete('/:idaccount', function(request, response) {
    account.delete(request.params.idaccount, function(err, result) {
        if (err) {
            return response.status(500).json({ status_code: response.statusCode, message: err });
        } else if (result.affectedRows === 0) {
            return response.status(404).json({ message: 'Tiliä ei löytynyt.' })
        }
        
        response.json(result);
    })
});

module.exports = router;
