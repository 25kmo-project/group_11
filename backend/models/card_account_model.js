const db = require('../database');

const card_account = {
    getAll:function(callback) {
        return db.query("SELECT * FROM card_account", callback);
    },

    getOne:function(idAccountCard, callback) {
        return db.query("SELECT * FROM card_account WHERE idcard_account=?",[idAccountCard], callback)
    },

    update:function(idCardAccount, idAccount, idCard, callback){
        return db.query("UPDATE card_account SET account_id=?, card_id=? WHERE idcard_account=?",[idAccount, idCard, idCardAccount],callback);
    },

    delete:function(idCardAccount, callback) {
        return db.query("DELETE FROM card_account WHERE idcard_account=?",[idCardAccount], callback)
    },
    
    getCardAccounts:function(idcard, callback){
        return db.query("SELECT * FROM card_account WHERE card_id=?",[idcard], callback);
    },
    addAccountToCard:function(idcard, idaccount, callback) {
        return db.query("INSERT INTO card_account (card_id, account_id) VALUES (?,?)",[idcard,idaccount], callback);
    },
    deleteAccountFromCard:function(idcard_account, callback) {
        return db.query("DELETE FROM card_account WHERE idcard_account=?",[idcard_account], callback);
    }
}

module.exports = card_account;