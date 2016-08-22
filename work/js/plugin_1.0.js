var http = require('http');

var qs = require('querystring');

var data = 
{
    a : 123 ,
    time : new Date().getTime()
};

var content = qs.stringify(data);

var options = 
    {
    hostname : 'www.baidu.com',
    port : 80 ,
    path : '/pay/pay_callback?' + content ,
    method : 'GET'
};

var req = http.request(options , function(res)
                       {
                           console.log('STATUS : ' + res.statusCode);
                           console.log('HEADERS : ' + JSON.stringify(res.headers));
                           res.setEncoding('utf8');
                           res.on('data' , function (chunk)
                                  {
                                      console.log('BODY : ' + chunk);
                                  });
                       });

req.on('error' , function(e)
       {
           console.log('problem with request : ' + e.message);
       });

req.end();
