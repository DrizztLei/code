#!/usr/bin/node

var http = require('http');

var options =
    {
    hostname : '192.168.1.4',
    port : 3000,
    method : 'POST',
    path : '/edison' ,
    headers : {'Connection' : 'keep-alive'},
};


/**
 * 如下特别的消息头应当注意：
 * 发送'Connection: keep-alive'头部将通知Node此连接将保持到下一次请求。
 * 发送'Content-length'头将使默认的分块编码无效。
 * 发送'Expect'头部将引起请求头部立即被发送。
 * 通常情况，当发送'Expect: 100-continue'时，你需要监听continue事件的同时设置超时。参见RFC2616 8.2.3章节以获得更多的信息。
 */



var req = http.request(options,function(res)
                       {
                           //  console.log(res);
                       console.log('STATUS:\n' + res.statusCode);
                       console.log('HEADERS:\n' + JSON.stringify(res.headers));
                       res.setEncoding('utf8');
                       res.on('data',function(chunk)
                              {
                                  console.log('BODY:\n' + chunk);
                              });

                       });

req.on('response',function()
       {
           console.log("response");
       });

req.on('connect',function()
       {
           console.log("connect");

       });

req.on('socket',function()
       {
           console.log("socket");

       });

req.on('upgrade',function()
       {
           console.log("upgrade");

       });

req.on('continue',function()
       {
           console.log("continue");

       });

//如果在请求过程中出现了错误（可能是DNS解析、TCP的错误、或者HTTP解析错误），返回的请求对象上的'error'的事件将被触发。
req.on('error',function(e)
       {
           console.log(e.message);
       });

/**
 * 源API：request.write(chunk, [encoding])
 * 说明：发送正文中的一块。用户可以通过多次调用这个方法将请求正文以流的方式发送到服务器。此种情况建议在建立请求时使用['Transfer-Encoding', 'chunked']请求头。
 * @param {Object or String} chunk 参数chunk应当是一个整数数组或字符串。
 * @param {String} encoding 参数encoding是可选的，仅在chunk为字符串时可用。
 */

req.write('data\n');

/**
 * 源API：request.end(chunk, [encoding])
 * 说明：完成本次请求的发送。如果正文中的任何一个部分没有来得及发送，将把他们全部刷新到流中。如果本次请求是分块的，这个函数将发出结束字符'0\r\n\r\n'。如果使用参数data，就等于在调用request.write(data, encoding)之后紧接着调用request.end()。
 * @param {Object or String} chunk 参数chunk应当是一个整数数组或字符串。
 * @param {String} encoding 参数encoding是可选的，仅在chunk为字符串时可用。
 * example: req.end(),req.end('data\n'),req.end('data','utf8'),req.end(chunk)
 */

req.end();

/**
 * 阻止一个请求。（v0.3.8中新增的方法。）
 */

//req.abort();
/**
 * 源API：request.setTimeout(timeout, [callback])
 * 说明：一旦给这个请求分配的是一个socket时此函数会被调用
 * @param {Number} timeout 毫秒
 * @param {Function} callback 回到函数
 */

req.setTimeout(1000,function()
               {

               });

/**
 * 源API :request.setNoDelay([noDelay])
 * 说明：默认有一定的延迟，设置为0表示无延迟
 * @param {Number} noDelay
 */

req.setNoDelay(0)

    /**
* 源API：request.setSocketKeepAlive([enable], [initialDelay])
*     类似同上
*/
