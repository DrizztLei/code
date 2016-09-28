{
    var http = require("http");
    var server = http.Server();
    var count = 0;

    server.on('request' , function (req , res)
    {
        count ++;
        console.log("Get the count : " , count );
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write('<h1>HTTP Server From Gentoo Linux</h1>');
        res.end('<p>Copyleft by Elvis Lei</p>');
    });

    server.on('data' , function (data){
        console.log(data);
    });

    server.listen(3389);
    
    console.log("HTTP Server is running.");
}
