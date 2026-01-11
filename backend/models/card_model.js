const db = require('../database');

const card = {
    getAll:function(callback){
        return db.query("SELECT * FROM card", callback);
    },

    getOne:function(idcard, callback){
        return db.query("SELECT * FROM card WHERE idcard=?",[idcard],callback);
    },

    add:function(card, callback){
        return db.query("INSERT INTO card (idcard,pin) VALUES(?,?)",[card.idcard,card.pin],callback);
    },

    check_pin:function(idcard, callback){
        return db.query("SELECT pin FROM card WHERE idcard=?", [idcard],callback);
    }
}

module.exports = card;