/**
 * Created by elvis on 8/29/16.
 */
/*
var cluster = require('cluster');
var initSharedMemory = require('sharedmemory').init({
    cache : {
        type : 'LRU' ,
        max : 1000
    }
});

// 创建共享内存的控制器
// 在master进程中，控制器负责维护共享内存
// 在worker进程中，控制器负责和master的控制器通信，通过IPC消息对共享内存进行读写操作

var sharedMemoryController = initSharedMemory;


// 创建共享内存的控制器
// 在master进程中，控制器负责维护共享内存
// 在worker进程中，控制器负责和master的控制器通信，通过IPC消息对共享内存进行读写操作

console.log("INFO");

if (cluster.isMaster) {
    while(true)
    {
        setTimeout(function () {
            console.log("SET THE VALUE");
            sharedMemoryController.set("value" , 12);
            console.log("DONE");
        } , 1000);
    }
} else {
    console.log("RUN IN ELSE");
    if (cluster.worker.id == 1)
    {
        // 第一个worker向共享内存写入一组数据，用a标记
        sharedMemoryController.set('a', [0, 1, 2, 3]);
    }
    if (cluster.worker.id == 2)
    {
        // 第二个worker从共享内存读取a的值
        sharedMemoryController.get('a', function(data) {
            console.log(data);  // => [0, 1, 2, 3]
            // 删除
            sharedMemoryController.remove('a');
        });
    }
}
*/

var get = null;

var cache = require('node-shared-cache');

var obj = new cache.Cache("test", 557056);

var aim = "TEMP";

obj.aim="hello";

get = 2;
var test = "1".toString();

console.log(2 > test);

obj.isSet=true;
var data = new Date();
obj.startTime=data.getTime();

/*
// setting property
obj.foo = "bar";
// getting property

console.log(obj.foo);
// enumerating properties

for(var k in obj);
Object.keys(obj);

// deleting property
delete obj.foo;
// writing objects is also supported

obj.foo = {'foo': 'bar'};
// but original object reference is not saved
var test = obj.foo = {'foo': 'bar'};

test === obj.foo; // false

// circular reference is supported.

test.self = test;
obj.foo = test;

// and saved result is also circular

test = obj.foo;
test.self === test; // true
    */