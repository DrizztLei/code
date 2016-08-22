/**
 * Created by elvis on 7/3/16.
 */
var fs = require("fs");

var data = fs.readFileSync('input.txt');

console.log(data.toString());

console.log("done");