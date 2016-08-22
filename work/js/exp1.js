/**
 * Created by elvis on 7/30/16.
 */

console.log("Run the start.js");
var net= require('net');

exports.temp = function(data)
{
    console.log(("INF TEMP : "  , data));
};

var server=net.createServer(function(socket){
    var time = new Date();
    //console.log(time.toLocaleString());

    console.log('CONNECT IN : ' + time.toLocaleString());

    exports.set=socket.on('data',function(data){
        console.log('GET INFO  : ' , data.toString());
    });

    socket.on('end',function(myData){
        console.log("CLOSE IN : " + time.toLocaleString());
    });
});

server.listen(7274,function(){
    console.log('SERVER STARTED . ')
});

exports.server = server;
console.log("Run the start.js over.");
//done();