/**
 * Created by  on 2016/7/11.
 */
var http = require('http');
var url = require('url');
var fs = require('fs');

function onRequest(request, response) {
    response.writeHead(200, {'Content-type': 'text/html'});
    response.write('Hello,edison');
    response.end();
}

http.createServer(onRequest).listen(8080);
console.log('Get the info');
