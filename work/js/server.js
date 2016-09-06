#!/usr/bin/node
/**
 * Created by elvis on 7/30/16.
 */

var port = 7274;
console.log("Run the server.js");
var net= require('net');

var server=net.createServer(function(socket)
                            {
                                var time = new Date();
                                    //console.log(time.toLocaleString());

                                socket.on('connect' , function()
                                          {
                                              console.log('CONNECT IN : ' + time.toLocaleString());        
                                          });

                                socket.on('data',function(data)
                                          {
                                              console.log('GET INFO  : ' , data.toString());
                                              shared.value = data;
                                          });

                                socket.on('end',function(myData)
                                          {
                                              console.log("CLOSE IN : " + time.toLocaleString());
                                          });

                                socket.on('error' , function(err)
                                          {
                                              if(err.code === 'EADDRINUSE'){
                                                  process.exit();
                                              } else{
                                                  console.log("Error for unknow situation.");
                                              }
                                          });
                            });

server.on('error' , function(err){
    if(err.code == 'EADDRINUSE')
        {
            console.log("SERVER STARTED BEFORE.");
            process.exit(0);
        }
})
	

server.listen(port,function(){
    console.log('SERVER STARTED . ')
});

console.log("Run the server.js over.");
