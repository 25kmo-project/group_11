var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var customerRouter = require ('./routes/customer');
var cardRouter = require('./routes/card')
var accountsRouter = require('./routes/accounts')
var loginRouter = require('./routes/login');
const authenticateToken = require('./middleware/auth');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/login', loginRouter);

// Suojatut reitit
app.use(authenticateToken);
app.use('/api/customer', customerRouter);
app.use('/api/card', cardRouter);
app.use('/api/accounts', accountsRouter);

module.exports = app;
