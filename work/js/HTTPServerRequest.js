{
    var http = require('http');
    var url = require('url');
    var util = require('util');

    var count = 0;
    http.createServer(function (req, res) {
        res.writeHead(200 , {"Content-Type": "text/plain"});
        var info = util.inspect(url.parse(req.url , true));
        //res.end(util.inspect(url.parse(req.url, true)));
        res.end(info);
        console.log("Return the info for : \n" , info);
        console.log("Get the count info for : " , count++);
    }).listen(3000);
    
    console.log("Server running .");
}