{
    var http = require('http');
    var querystring = require('querystring');
    
    var contents = querystring.stringify({
        /*
        name : "ELvis",
        email : "elvis.linuxer@gmail.com",
        address : "Ji\'nan SDU"
        */
        name : 'byvoid',
        email : 'byvoid@byvoid.com',
        address : 'Zijing 2# , Tsinghua University'
    });
    
    var options = {
        /*
        hosts : 'wwww.byvoid.com',
        path : '/home/elvis/work/js/main.js',
        method : "POST",
        headers:{
            'Content-Type' : "application/x-www-form-urlencoded",
            'Content-Lenght' : contents.length
        }
        */
        host : 'www.byvoid.com',
        path : '/application/node/post.php',
        method : 'POST',
        headers : {
            'Content-Type' : 'application/x-www-form-urlencoded',
            'Content-Lenght' : contents.length
        }
    };
    try
    {
        var req = http.request(options , function (res) 
        {
            res.setEncoding('utf8');
            res.on('data' , function (data) 
            {
                console.log(data);
            });
        });    
    }catch(e) {
        console.log("Get the error");
        console.log(e);
    }

    req.write(contents);
    req.end();

}
