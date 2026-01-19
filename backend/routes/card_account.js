const express = require("express");
const router = express.Router();
const cardContoller = require('../controllers/card_controller');

router.post('/accounttocard', function(request,response){
    //Function check does card have a debit or credit account
    cardContoller.authAccountAdd(request, response)
});

router.post('/removeaccountfromcard', function(request, response){
    //Controller check does card have rights to given account
    cardContoller.accountRemove(request,response)
});

module.exports = router;