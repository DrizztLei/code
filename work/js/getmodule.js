{
    var myModule = require('./module');
    myModule.setName('EVA');
    myModule.sayHello();
    console.log("Get the info");
    console.log(process.argv);
    process.stdin.resume();
    process.stdin.on('data' , function (data)
    {
        process.stdout.write('read from console : ' + data.toString());
    });
    console.log("Run not over here.");
}