var model = "/home/elvis/work/opencv/pattern_recognition/LBPHF.cv.model";
var input = "/home/elvis/work/opencv/pattern_recognition/orl_faces/s26/7.pgm";
var script = "/home/elvis/work/opencv/pattern_recognition/recognize.sh";
var spawn = require('child_process').spawn;
command = spawn(script , ['-M' , model , '-I' , input]);

command.stdout.on('data' , function(data){
    console.log('standard output:\n' + data);
});

command.stderr.on('data' , function(data){
    console.log("standard error output:\n" + data);
});

command.on('exit' , function(code , signal){
    console.log("child process exit with : " + code);
});
