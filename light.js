var addon = require('./build/Release/helloworld');

exports.toggle = function(req, res){
  res.send(addon.hello());
}
exports.explain = function(req, res){
  res.send('Please use only /toggle/lcd');
}

