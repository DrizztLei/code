#!/usr/bin/node
var http = require("http");
var port = 3000;
var server = new http.Server();
var script = "/home/elvis/work/js/search.sh";
var spawn = require('child_process').spawn;

var accept = function(req , res)
{
    // console.log(req.url);
    
    var back = function(req , res)
    {
        var temp = require('./device');
        temp = JSON.stringify(temp);
        console.log(temp);
        res.writeHeader(200 , {'Content-Type' : 'text/plain'});
        res.write(temp);
        res.end();
    };

    command = spawn(script , [req.url]);

    command.stdout.on('data' , function(data)
            {
                console.log("Data : " + data);
            });
    
    command.stderr.on('data' , function(data)
            {
                console.log("Err : " + data);
            });

    command.on('exit' , function(code , signal)
            {
                console.log("CODE " + code);
                if(code == 0)
                {
                    back(req , res); 
                }
                else
                {
                    console.log("Error for your mistake"); 
                }
            });


    //async.eachSeries(spawn(script , ['' , req.url]) , back(req , res));
};


server.on('request',accept);

/*
   {

   if(req.url == "/home/elvis/work/getinfo")
   {
   console.log("run the hardware and get the info");
   res.writeHeader(200 , {'Content-Type' : 'text/plain'});
   res.end('You will get the info sooner or later');
   }	
   else
   {
   console.log("get the info and store the message for the user who wanna it");
   res.writeHeader(200 , {'Content-Type' : 'text/plain'});
   res.end("I have got your info here");
   }
   });
   */

server.on('connection',function(socket){
    //    console.log("connection");
});

server.on('close',function(){
    console.log("close");
});

server.on('checkContinue',function(req,res){
    console.log("check continue");
});

server.on('connect',function(req,socket,head){
    console.log("connect");
});

server.on('upgrade',function(req,socket,head){
    console.log("upgrade");
});

server.on('clientError',function(exception,socket){
    console.log("client error");
});

server.maxHeadersCount = 1000;

server.setTimeout(1000,function(){
    console.log("client error");
});

server.timeout = 120000;

server.listen(port ,function(){
    console.log('Listen port ' + port);
});
