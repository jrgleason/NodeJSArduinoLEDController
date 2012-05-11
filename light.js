var addon = require('./build/Release/helloworld');

exports.toggle = function(req, res){
  res.send(addon.hello());
}
exports.explain = function(req, res){
  res.send('Please use only /toggle/lcd');
  // not sure why you were invoking addon.hello() here, but
  // you could still do that, no need for the return either
}

