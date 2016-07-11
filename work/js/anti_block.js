/**
 * Created by elvis on 7/3/16.
 */
var fs = require("fs");

fs.readFile('input.txt' , function(err , data)
{
    if (!err)
    {
        console.log(data.toString());
    }
    else
    {
        return console.error(err);
    }
});
console.log("Process done.");
