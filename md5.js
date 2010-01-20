var hashlib = require("./build/default/hashlib");
var sys = require("sys");
var md5 = require("./test/md5");
var c=new hashlib.hashlib();
sys.puts(c.md5('test'));
