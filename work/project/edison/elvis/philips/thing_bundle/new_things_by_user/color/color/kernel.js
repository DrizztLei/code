console.log("run the kernel.js");
var script = "/home/elvis/work/jar/philips.sh";
var jar = "/home/elvis/work/jar/philips.jar";
var spawn = require('child_process').spawn;
//console.log(IN.in);
//var temp = "45 155 245";
command = spawn( script , ['-J' , jar , '-I' , IN.in]);
//command = spawn ( script , ['-J' , jar , '-I' , temp]);

command.stdout.on('data' , function(data){
    console.log('standard output:\n' + data);
    IN.status = true;
    sendOUT({status:true});
});

command.stderr.on('data' , function(data){
    console.log("standard error output:\n" + data);
//  IN.isDone = err;
    IN.status = false;
    sendOUT({status:false});
});

command.on('exit' , function(value , signal){
    console.log("child process exit with : " + value);
    IN.code = value;
   //sendOUT({code:value});
});
console.log("run the kernel.js over");
