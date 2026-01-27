const db = require('../database');

const card_actions = {
    //withdraw ja deposit proseduurit:
    //tarkistaa onko debit vai credit
    //tarkistaa käytettävissä olevat varat
    //tekee asettaa noston tai talletuksen jälkeisen saldon tietokantaan
withdraw:function(accountid, amount, callback){
    return db.query("CALL withdraw(?, ?)", [amount, accountid], callback);
},
deposit:function(accountid, amount, callback){
    return db.query("CALL deposit(?,?)", [amount, accountid], callback);
},
}

module.exports=card_actions;