/**
 * Created by elvis on 7/29/16.
 */

/*
myDate.getYear();        //获取当前年份(2位)
myDate.getFullYear();    //获取完整的年份(4位,1970-????)
myDate.getMonth();       //获取当前月份(0-11,0代表1月)
myDate.getDate();        //获取当前日(1-31)
myDate.getDay();         //获取当前星期X(0-6,0代表星期天)
myDate.getTime();        //获取当前时间(从1970.1.1开始的毫秒数)
myDate.getHours();       //获取当前小时数(0-23)
myDate.getMinutes();     //获取当前分钟数(0-59)
myDate.getSeconds();     //获取当前秒数(0-59)
myDate.getMilliseconds();    //获取当前毫秒数(0-999)
myDate.toLocaleDateString();     //获取当前日期
var mytime=myDate.toLocaleTimeString();     //获取当前时间
myDate.toLocaleString( );        //获取日期与时间
*/
//var misc = require("./misc");
var net= require('net');

var server=net.createServer(function(socket){
    var time = new Date();
    //console.log(time.toLocaleString());

    console.log('CONNECT IN : ' + time.toLocaleString());

    socket.on('data',function(data){
        console.log('GET INFO  : ' , data.toString());
 });

    socket.on('end',function(myData){
        console.log("CLOSE IN : " + time.toLocaleString());
    });
});

server=net.createServer(function(socket){
    var time = new Date();
    //console.log(time.toLocaleString());

    console.log('CONNECT IN : ' + time.toLocaleString());

    socket.on('data',function(data){
        console.log('GET INFO  : '  + data);
    });

    socket.on('end',function(myData){
        console.log("CLOSE IN : " + time.toLocaleString());
    });

    socket.on('close', function(data) {
        console.log('SERVER CLOSE IN : ' + time.toLocaleString());
    });
});

//启动服务
server.listen(7274,function(){
    console.log('SERVER STARTED . ')
});

server=net.createServer(function(socket){
    var time = new Date();
    //console.log(time.toLocaleString());

    console.log('CONNECT IN : ' + time.toLocaleString());

    socket.on('data',function(data){
        console.log('UNKNOW : '  );
    });

    socket.on('end',function(myData){
        console.log("CLOSE IN : " + time.toLocaleString());
    });

    socket.on('close', function(data) {
        console.log('SERVER CLOSE IN : ' + time.toLocaleString());
    });
});

console.log("I get it .");

server.on('data' , function (socket){
    socket.on('data' , function(data){
        console.log("YOU DID.");
    });
});

/*
server.close();
server.listen(7274,function(){
    console.log('SERVER STARTED . ')
});
*/