var addon = require('./build/Release/helloworld');

exports.toggle = function(request, response){
	response.writeHead(200, {"Content-Type": "text/plain"});
     	var value = "Command not recognized";
	if('/led/toggle' == request.url){
        	value=addon.hello();
     	}	
     	response.write(value);
	response.end();
	return value; 
}
exports.explain = function(request, response){
        response.writeHead(200, {"Content-Type": "text/plain"});
        response.write("Please use only /toggle/lcd");
        response.end();

        return addon.hello();
}

