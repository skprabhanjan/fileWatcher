var express = require('express');
var router = express.Router();
const fs = require('fs');


/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

/////

router.get('/connect',function(req,res,next){
    var client_address = req.query.client_address;
fs.writeFile("./mvc_watcher/client.txt", client_address, function (err) {
    if (err) {
      return console.log(err);
    }
  });
  
    var all_files = [];
    fs.readdir("/Users/prabhanjansk/uspPrograms", (err, files) => {
      files.forEach(file => {
          all_files.push(file);
      });
      res.send(all_files);
    });
})

module.exports = router;
