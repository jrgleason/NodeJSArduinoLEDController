var light = require('./light.js');
var express = require('express');
var app = express.createServer();
console.log("Test");
app.use(express.favicon());
app.get('/',light.toString);
app.get('/led/toggle', light.toggle);
app.listen(8888);

