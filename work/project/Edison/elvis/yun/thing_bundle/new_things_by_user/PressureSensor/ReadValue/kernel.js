/**
 * Created by elvis on 7/30/16.
 */

//var port = 7274;
//var importServer = require("./start.js");
//var events = require("events");

if(IN.switch)
{
   /*
   IN.value = shared.value;
   sendOUT({value : IN.value});
   console.log("SEND TRUE");
   */
   var cache = require('node-shared-cache');
   var reader = new cache.Cache("VALUE" , 557056);
   console.log("RUN IN IF");
   console.log(reader.value);
}
else
{
   /*
   IN.value = shared.value;
   //sendOUT({value : IN.value});
   console.log("SEND FALSE");
   */
   console.log("RUN IN ELSE");
}

function portIsOccupied (port) {
    var net = require('net');

    var server = net.createServer().listen(port)

    server.on('listening', function () {
        server.close() 
        console.log('The port of ' + port + ' is available.') 
    });

    server.on('error', function (err) {
        if (err.code === 'EADDRINUSE') { 
            console.log('The port of ' + port + ' is occupied, please change other port.')
        }
    });
}
