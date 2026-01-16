const db = require('../database');

const account_customer = {
    getAll:function(callback){
        return db.query("SELECT * FROM account_customer", callback);
    },
    getOne:function(idaccount_customer, callback){
        return db.query("SELECT * FROM account_customer WHERE idaccount_customer=?", [idaccount_customer],callback);
    },
    //db.query to make sure that there is not owner marked for account
    add:function (account_customer, callback) {
        db.query("SELECT account_id FROM account_customer WHERE account_id = ?", [account_customer.account_id],
        function (err, rows) {
            if (rows.length > 0) {
                return callback(null, {message: "et voi asettaa yhdelle tilille toista omistajaa"});
            }
                return db.query(
                "INSERT INTO account_customer (customer_id, account_id) VALUES (?, ?)", [account_customer.customer_id, account_customer.account_id], callback);
        });
    },

    update:function(account_customer, idaccount_customer, callback){
        db.query("SELECT account_id FROM account_customer WHERE account_id=?", [account_customer.account_id],
            function(err, rows){
                if(rows.length > 0){
                    return callback(null, {message: "et voi asettaa yhdelle tilille toista omistajaa"});
                }
                    return db.query("UPDATE account_customer SET customer_id=IFNULL(?,account_customer.customer_id), account_id=IFNULL(?, account_customer.account_id) WHERE idaccount_customer=?", [account_customer.customer_id, account_customer.account_id, idaccount_customer], callback);
            });
    },

    delete:function(idaccount_customer, callback){
        return db.query("DELETE FROM account_customer WHERE idaccount_customer=?", [idaccount_customer], callback);
    },
};
//account_customer taulukossa on merkitty käyttäjät joilla on oikeudet tiettyihin tileihin.

module.exports=account_customer;