const db = require('../database');

const customer={
getAll:function(callback){
    return db.query("SELECT * FROM customer");
},
getOne:function(idcustomer, callback){
    return db.query("SELECT * FROM customer where idcustomer=?", [idcustomer], callback);
},
add:function(customer, callback){
    return db.query("INSERT INTO customer VALUES (?,?,?,?)", [customer.fname, customer.lname, customer.street_address, customer.city, callback]);
},
update:function(customer, idcustomer, callback){
return db.query("UPDATE FROM customer SET fname=?, lname=?, street_address=?, city=? where idcustomer=?", [customer.fname, customer.lname, customer.street_address, customer.city, idcustomer, callback]);
},

delete:function(idcustomer, callback){
return db.query("DELETE customer WHERE idcustomer=?", [idcustomer], callback);
}

};

module.exports=customer;