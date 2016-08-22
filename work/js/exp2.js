/**
 * Created by elvis on 7/30/16.
 */

var port = 7274;
var importServer = require("./exp1.js");
var events = require("events");

if(true)
{
    if(portIsOccupied(port))
    {
        var net= require('net');

        var server=net.createServer(function(socket){
            var time = new Date();

            console.log('CONNECT IN : ' + time.toLocaleString());

            socket.on('data',function(data){
                console.log('GET INFO  : ' , data.toString());
            });

            socket.on('end',function(myData){
                console.log("CLOSE IN : " + time.toLocaleString());
            });
        });

        server.listen(port,function(){
            console.log('SERVER STARTED . ')
        });
    }
    else
    {
        console.log("temp");
    }
}
else
{
    if(portIsOccupied(port))
    {
            importServer.set=socket.on('data',function(data){
                console.log('GET INFO  : ' , data.toString());
                //IN.value = data;
            });
    }
}

// 检测端口是否被占用
function portIsOccupied (port) {
    // 创建服务并监听该端口
    var net = require('net');

    var server = net.createServer().listen(port)

    server.on('listening', function () { // 执行这块代码说明端口未被占用
        server.close() // 关闭服务
        console.log('The port【' + port + '】 is available.') // 控制台输出信息
    });

    server.on('error', function (err) {
        if (err.code === 'EADDRINUSE') { // 端口已经被使用
            console.log('The port【' + port + '】 is occupied, please change other port.')
        }
    });
}