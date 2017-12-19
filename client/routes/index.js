var express = require('express');
var router = express.Router();
var path = require('path');
var fs = require('fs');
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

io.on('connection', function(socket){
  console.log('a user connected');
  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
});
/* GET home page. */
router.get('/', function(req, res, next) {
  //res.render('index', { title: 'Express' });
  res.sendFile(path.join(__dirname+'/index.html'));
});

router.get('/file_changed',function(req,res,next){
    filename = req.query.filename || "nothing";
    //res.render('index', { title: filename });
    //res.sendFile(path.join(__dirname+'/test.html'));
    //res.send("updated");
});

module.exports = router;
