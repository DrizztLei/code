{
    
    var http = require('http');
    var querystring = require('querystring');
    var util = require('util');

    function init(req , res) {
        var post = '';
        req.on('data' , function (req, res) {
            post += chunk;    
        });
    }
    
    function getvalue() {
        return ;
    }
    
    var x = getvalue();
    
    console.log(x);

    var adapter = init;

    http.createServer(adapter).listen(2000);
    
    console.log("Get info");

}