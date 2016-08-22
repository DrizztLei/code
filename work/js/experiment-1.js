{


    console.log(process.argv);
    console.log(process.argv[0]);
    console.log(process.argv[1]);
    console.log(process.argv[2]);

    var util = require('util');

    function Base() 
    {
        this.name = 'base';
        this.base = 1991;
        this.sayHello = function () 
        {
            console.log('Hello' + this.name);
        };
    }
    
    Base.prototype.showName = function ()
    {
        console.log(this.name);
    };

    function Sub()
    {
        this.name = 'Sub';
    }

    util.inherits(Sub , Base);

    var objSub = new Base();
    objSub.showName();
    var Son = new Sub();

    //console.log(objSub);
}