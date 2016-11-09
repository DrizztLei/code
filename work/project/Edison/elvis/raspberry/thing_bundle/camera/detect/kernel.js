console.log("kernel.js");
if(IN.detect)
{
    var process = require('child_process');
	process.exec("/home/elvis/enviroment/iot-sol/node_modules/hope-demo/raspberry/thing_bundle/camera/detect/detect.sh" , function (error,stdout,stderr) {
		if (error !== null)
		{
		  console.log("Error :" + error);
		}
		if (stdout !== null)
		{
		    console.log(stdout);
		}
		if(stderr !== null)
		{
		    console.log("Error output : " + stderr);
		}
	});
    IN.out = true;
    sendOUT({out:true});
}
