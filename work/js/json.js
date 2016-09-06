#!/usr/bin/node

var json = 
    {
    a : ['1'],
    b : ['2'],
    c : ['3']
}

var string = JSON.stringify(json);

console.log(string);

console.log(JSON.parse(string));

console.log(json['a']);
