var express = require('express');
var router = express.Router();
var account = require('../models/account_model');
var validateFields = require('../middleware/validateFields');

const required_fields = ['idaccount', 'balance', 'account_type', 'credit_limit', 'idowner']

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

    if (result.length === 0) {
      return response.status(404).json({ status_code: response.statusCode, message: 'User not found.' })
    }

    response.json(result);
  })
});

router.post('/', validateFields(required_fields), function(request, response) {
  account.create(request.body, function(err, result) {
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

// Field validation is performed to return more verbose errors for API caller
router.put('/:idaccount', validateFields(required_fields), function(request, response) {
  account.update(request.body, request.params.idaccount, function(err, result) {
    if (err) {
      return response.status(500).json({ status_code: response.statusCode, message: err });
    }

    if (result.affectedRows === 0) {
      return response.status(404).json({ message: 'User not found.' })
    }

    response.json(result);    
  })
});

router.patch('/:idaccount', function(request, response) {
  account.update(request.body, request.params.idaccount, function(err, result) {
    if (err) {
      return response.status(500).json({ status_code: response.statusCode, message: err });
    }

    if (result.affectedRows === 0) {
      return response.status(404).json({ message: 'User not found.' })
    }

    response.json(result);
  })
});

router.delete('/:idaccount', function(request, response) {
  account.delete(request.params.idaccount, function(err, result) {
    if (err) {
      return response.status(500).json({ status_code: response.statusCode, message: err });
    } 

    if (result.affectedRows === 0) {
      return response.status(404).json({ message: 'User not found.' })
    }

    response.json(result);
  })
});

module.exports = router;
