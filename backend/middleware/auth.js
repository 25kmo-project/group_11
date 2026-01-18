const jwt = require('jsonwebtoken');

function authenticateToken(req, res, next) {
    console.log(req);
    const authHeader = req.headers['authorization'];
    // Extract token by removing "Bearer " prefix from "Bearer "
    const token = authHeader && authHeader.split(' ')[1];
    console.log("Token:", token);
    // console.log(authHeader.split(' ')[1]);
    if (token == null) return res.sendStatus(401);
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
        if (err) {
            return res.sendStatus(403);
        }
        req.user = user;
        // console.log("req.user:", req.user);
        next();
    });
}

module.exports = authenticateToken;

