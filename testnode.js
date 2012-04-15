var addon = require('./build/Release/helloworld');

var http = require("http");

http.createServer(function(request, response) {
  if(!('/favicon.ico' == request.url)){
     response.writeHead(200, {"Content-Type": "text/plain"});
     response.write(addon.hello());
     response.end();
  }
}).listen(8888);

