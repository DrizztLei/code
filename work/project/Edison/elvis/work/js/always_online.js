var http=require('http');  

http.createServer(function(req,res)
{  
    var status = req.url.substr(1);
    if( ! http.STATUS_CODES[status])
    {
	    status = '404';
    }
    res.writeHeader(status,{'Content-Type':'text/html'});  
    res.write('<h1>Server</h1>');  
    res.end('<p>From Edision</p>');  
}).listen(80);  
  
console.log('HTTP server is listening at port 80'); 
