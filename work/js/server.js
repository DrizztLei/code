var http = require("http");

http.createServer(function (request , response){
    // send the head of the http
    // status of http : 200 : ok
    // content : text/plain
    response.writeHead(200 , {'Content-Type' : 'text/plain'});

    // send the response message : "Hello World"
    response.end("Hello World\n");

}).listen(8888);

console.log('Server running at http://127.0.0.1:8888/');
