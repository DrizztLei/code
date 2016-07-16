{
    var event = require('events');
    var emitter = new event.EventEmitter();

    emitter.on('Action' , function (argv1 , argv2) {
       console.log("Get the info for : "  , argv1 , argv2);
    });

    emitter.emit('Action' , 'Evlis' , "\tLei");

    console.log("------------------Get the value done ----------------");

    var fs = require('fs');
    fs.readFile('input.txt' , 'utf-8', function (err , data) {
       if(err)
       {
           console.log(err);
       }
       else
       {
           console.log(data);
           /*
           for(var i = 0 ; var < data.length(); i++)
           {
               console.log(data[i]);
           }
           */
           for (count in data)
           {
               console.log(data[count]);
           }
       }
    });

    console.log("predeal done . server starting.");
    var http = require('http');
    var count = 0;
    http.createServer(function (req , res)
    {
       res.writeHead(200 , {'Content-Type': 'text/html'});
       res.write('<h1>Server From Gentoo Linux by Elvis Lei</h1>');
       res.end('<p>Get the response</p>');
    }).listen(3000);

    console.log("Http Server Started .")
}