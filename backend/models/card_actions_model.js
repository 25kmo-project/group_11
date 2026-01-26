const db = require('../database');

const card_actions = {
withdrawal:function(accountid, withdrawAmount, callback){
    return db.query("CALL withdrawal(?, ?)" [withdrawAmount, accountid], callback);
}


}

module.exports=card_actions;