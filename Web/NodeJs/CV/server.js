
var port = process.env.PORT || 1337;


var express = require("express");
var element = require("./Element.js");
var app = express();

app.use(express.static("autres"));

app.get('/', function (req, res) {
    res.end(element.traitement("acceuil"));
});

app.get('/:page', function (req, res) {
    res.end(element.traitement(req.params.page));
});

app.use(function (req, res) {
    res.end(element.traitement("erreur"));
});

app.listen(port);

