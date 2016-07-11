{
    
    function doSometing( argc , callback) {
        console.log("before doing . ");
        callback();
    }

    doSometing(function onEnd() {
       console.log("On end.");
    });
}