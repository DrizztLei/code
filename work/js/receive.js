/**
 * Created by elvis on 8/29/16.
 */

var cache = require('node-shared-cache');
var obj = new cache.Cache("test", 557056);

console.log(obj.aim);


console.log(obj.isSet);


console.log(obj.startTime);

var date = new Date();

console.log(date.getTime() - obj.startTime );

console.log(obj.startTime == null);