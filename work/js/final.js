/**
 * Created by elvis on 7/30/16.
 */
var net = require('net');

var HOST = '192.168.1.2';
var PORT = 7274;

var server = net.createServer(function(sock) {

    // 我们获得一个连接 - 该连接自动关联一个socket对象
    console.log('CONNECTED: ' +
        sock.remoteAddress + ':' + sock.remotePort);

    // 为这个socket实例添加一个"data"事件处理函数
    sock.on('data', function(data) {
        console.log('DATA ' + sock.remoteAddress + ': ' + data);
        // 回发该数据，客户端将收到来自服务端的数据
        sock.write('You said "' + data + '"');
        sock.destroy();
    });

    close(function(){
        console.log("Server close.");
    });
    sock.close(function(){
        console.log("sock close.");
    });
    sock.destroy(function(){
        console.log("destory close.");
    });

    // 为这个socket实例添加一个"close"事件处理函数
    sock.on('close', function(data) {
        console.log('CLOSED: ' +
            sock.remoteAddress + ' ' + sock.remotePort);
    });

}).listen(PORT, HOST);

server.close(function(){
    console.log("JFDKFJ");
});

server = null;

server = net.createServer(function(sock) {
    // 我们获得一个连接 - 该连接自动关联一个socket对象
    console.log('CONNECTED: ' +
        sock.remoteAddress + ':' + sock.remotePort);

    // 为这个socket实例添加一个"data"事件处理函数
    sock.on('data', function(data) {
        console.log('DATA ' + sock.remoteAddress + ': ' + "fhahahahahahhaha");
        // 回发该数据，客户端将收到来自服务端的数据
    });

    close(function(){
        console.log("Server close.");
    });
    sock.close(function(){
        console.log("sock close.");
    });
    sock.destroy(function(){
        console.log("destory close.");
    });

    // 为这个socket实例添加一个"close"事件处理函数
    sock.on('close', function(data) {
        console.log('CLOSED: ' +
            sock.remoteAddress + ' ' + sock.remotePort);
    });
}).listen(HOST , PORT);

