var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var port = process.env.PORT || 8080;
var all_connections = [];
app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket){
  console.log("connection");
  all_connections.push(socket);
  // socket.on('chat message', function(msg){
  //   io.emit('chat message', msg);
  // });
});


app.get('/file_changed',function(req,res,next){
  filename = req.query.filename || "nothing";
  all_connections.forEach(function(socket){
      socket.emit('notification',filename);
  });
  //current_connection.emit('notification',filename);
  res.send("updated");
});

http.listen(port, function(){
  console.log('listening on *:' + port);
});
