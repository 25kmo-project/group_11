var express = require('express');
var router = express.Router();
var account = require('../models/account_model');

/* GET accounts listing. */
router.get('/', function(request, response) {
  account.getAll(function(err, result) {
    if (err) {
      response.send(err);
    } else {
      response.json(result);
    }
  })
});

router.get('/:account_id', function(request, response) {
  account.getOne(request.params.account_id, function(err, result) {
    if (err) {
      response.send(err);
    } else {
      response.json(result);
    }
  })
});

router.post('/', function(request, response) {
  account.create(request.body, function(err, result) {
    if (err) {
      response.send(err);
    } else {
      response.json(result);
    }
  })
});

router.put('/:account_id', function(request, response) {
  account.update(request.body, request.params.account_id, function(err, result) {
    if (err) {
      response.send(err);
    } else {
      response.json(result);
    }
  })
});

router.patch('/:account_id', function(request, response) {
  account.update(request.body, request.params.account_id, function(err, result) {
    if (err) {
      response.send(err);
    } else {
      response.json(result);
    }
  })
});

router.delete('/:account_id', function(request, response) {
  account.delete(request.params.account_id, function(err, result) {
    if (err) {
      response.send(err);
    } else {
      response.json(result);
    }
  })
});

module.exports = router;
