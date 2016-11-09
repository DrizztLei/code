/**
 * Created by elvis on 7/30/16.
 */
var script = "/home/elvis/work/yun-init/server.sh";
var spawn = require( 'child_process' ).spawn;

command = spawn(script, ['-p' , process.pid]);

/*
command.stdout.on('data' , function(data)
		{
			console.log(data);	
		}
		);

command.stderr.on('data' , function(data)
		{
			console.log(data);
		});
*/

command.on('exit' , function(value , signal){
    if(value === 0)
        {
            console.log("    4.5  hub        SHELL EXIT WITH CODE 0");
        }
        else{
            console.log("    4.5  hub        SEHLL EXIT WITH CODE 1");
        }
});
done();
