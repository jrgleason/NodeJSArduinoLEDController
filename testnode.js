var addon = require('./build/Release/helloworld');

var http = require("http");

http.createServer(function(request, response) {
  if(!('/favicon.ico' == request.url)){
     response.writeHead(200, {"Content-Type": "text/plain"});
     if('/led/toggle' == request.url){
     	response.write(addon.hello());
     }
     else{
        response.write("Command not recognized");
     }
     response.end();
  }
}).listen(8888);

