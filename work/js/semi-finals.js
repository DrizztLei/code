#!/usr/bin/node
/**
 * Created by elvis on 7/30/16.
 */

var port = 7274;
//console.log("Run the server.js");
var http = require('http');
//console.log("run the kernel.js");

var script = "/home/elvis/work/jar/philips.sh";
var jar = "/home/elvis/work/jar/philips.jar";
var spawn = require('child_process').spawn;

var server = http.createServer(function (req, res) {

    var time = new Date();

    //console.log("START IN : " + time.toLocaleString());

    switch (req.method) {

        case 'POST':
        req.on('data', function (data) {

                var json = eval("(" + data.toString() + ")");

                console.log(json);

                console.log(json["R"]);
                console.log(json["G"]);
                console.log(json["B"]);

                var value = "0 ";

                value += json["R"] + " ";
                value += json["G"] + " ";
                value += json["B"] + " ";

                console.log(value);

            //command = spawn(script, ['-J', jar, '-I', value]);

                /*
                command.stdout.on('data', function (data) {
                    console.log('standard output:\n' + data);
                });

                command.stderr.on('data', function (data) {
                    console.log("standard error output:\n" + data);
                });

                command.on('exit', function (value, signal) {
                    console.log("child process exit with : " + value);
                });
               */

            });
    }

    req.on('end', function (myData) {
        console.log("CLOSE IN : " + time.toLocaleString());
    });
});

server.listen(port);
//console.log("Run the server.js over.");
