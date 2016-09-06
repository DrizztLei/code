/**
 * Created by elvis on 7/30/16.
 */
console.log("run the kernel.js");
if(IN.in)
{
var script = "/home/elvis/work/jar/konke.sh";
var jar = "/home/elvis/work/jar/konke.jar"
var spawn = require('child_process').spawn;

//var temp = "45 155 245";

    command = spawn( script , ['-J' , jar , '-I' , "3 key open"]);
//command = spawn ( script , ['-J' , jar , '-I' , temp]);

    command.stdout.on('data' , function(data){
    if(data.length != 2048)
    {    
        console.log('standard output:\n' + data);
        IN.status = data;
        sendOUT({status:data});        
    }
});

    command.stderr.on('data' , function(data){
    console.log("standard error output:\n" + data);
//  IN.isDone = err;
    IN.status = data;
    sendOUT({status:data});
});

    command.on('exit' , function(value , signal){
    console.log("child process exit with : " + value);
    IN.code = value;
   //sendOUT({code:value});
});  
}

console.log("run the kernel.js over");
