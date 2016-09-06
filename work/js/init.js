#!/usr/bin/node

/**
 * Created by elvis on 7/30/16.
 */

var script = "/home/elvis/server.sh";
var spawn = require( 'child_process' ).spawn;
command = spawn(script, ['--parameter' , "REDEMPTION"]);

command.on('exit' , function(value , signal){
    if(value === 0)
        {
            console.log("EXIT WITH CODE 0");
        }
        else{
            console.log("EXIT WITH CODE 1");
        }
});
