//var model = "/home/elvis/work/opencv/pattern_recognition/LBPHF.cv.model";
var script = "/home/elvis/work/opencv/pattern_recognition/recognize.sh";
var spawn = require('child_process').spawn;
command = spawn(script , ['-M' , IN.model , '-I' , IN.input]);

command.stdout.on('data' , function(data){
    console.log('standard output:\n' + data);
    IN.out = data;
    sendOUT({out:data});
});

command.stderr.on('data' , function(data){
    console.log("standard error output:\n" + data);
    IN.isDone = err;
    sendOUT({isDone:err});
});

command.on('exit' , function(value , signal){
    console.log("child process exit with : " + value);
    IN.code = value;
    sendOUT({code:value});
});
