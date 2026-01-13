const db = require('../database')

const account = {
    getAll:function(callback) {
        return db.query('SELECT * FROM account', callback);
    },
    getOne:function(account_id, callback) {
        return db.query('SELECT * FROM account WHERE idaccount=?', [account_id], callback);
    },
    create:function(account, callback) {
        return db.query(
            'INSERT INTO account (idaccount, account_type, credit_limit, idowner) VALUES (?,?,?,?)', 
            [account.account_id, account.account_type, account.credit_limit, account.owner_id],
            callback
        );
    },
    update:function(account, account_id, callback) {
        return db.query(
            'UPDATE account SET idaccount=IFNULL(?, idaccount), balance=IFNULL(?, balance), account_type=IFNULL(?, account_type), credit_limit=IFNULL(?, credit_limit), idowner=IFNULL(?, idowner) WHERE idaccount=?', 
            [account.account_id, account.balance, account.account_type, account.credit_limit, account.owner_id, account_id],
            callback
        );
    },
    delete:function(account_id, callback) {
        return db.query('DELETE FROM account WHERE idaccount=?', [account_id], callback);
    },
}

module.exports=account;