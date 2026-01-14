const db = require('../database');

const transaction={
    getAllUser:function(idaccount, callback){
        return db.query("SELECT * FROM transaction where idaccount=?", [idaccount], callback);
    },
    getOne:function(idtransaction, callback){
        return db.query("SELECT * FROM transaction where idtransaction=?", [idtransaction], callback);
    },
    create:function(transaction, callback){
        return db.query(
            'INSERT INTO transaction (idaccount, amount, transaction_type, timestamp) VALUES (?,?,?,?)',
            [transaction.idaccount, transaction.amount, transaction.transaction_type, transaction.timestamp],
            callback
        );
    },
    update:function(transaction, idtransaction, callback){
        return db.query(
            'UPDATE transaction SET idaccount=IFNULL(?, idaccount), amount=IFNULL(?, amount), transaction_type=IFNULL(?, transaction_type), timestamp=IFNULL(?, timestamp) WHERE idtransaction=?',
            [transaction.idaccount, transaction.amount, transaction.transaction_type, transaction.timestamp, idtransaction],
            callback
        );
    },
    delete:function(idtransaction, callback){
        return db.query('DELETE FROM transaction WHERE idtransaction=?', [idtransaction], callback);
    }
};

module.exports=transaction;