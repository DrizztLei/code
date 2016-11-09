#!/usr/bin/node

var net = require('net');

var host = "192.168.1.11";

var port = 7676;

var client = new net.Socket();

client.connect(port , host , function()
               {
                   var value = "pause";
                   console.log("Send the fsr value to server");
                   client.write("" + value);
                   client.destroy();
               });

client.on('data' , function(data)
          {
              console.log("data : " + data);
              client.destroy();
          });

client.on('close' , function()
          {
              console.log("Connection  closed");
          });

