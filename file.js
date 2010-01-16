var hashlib = require("./build/default/hashlib");
var sys = require("sys");


sys.puts(hashlib.md5_file('./test.js'));


hashlib.md5_file('./test.js',function(value) {
	sys.puts(value);
});
