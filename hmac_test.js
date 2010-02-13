var hashlib = require("./build/default/hashlib");
var sys = require("sys");
var md5 = require("./test/md5");

process.chdir(__dirname);

sys.puts(hashlib.hmac_sha1('testsjdfhskjdfhskjfhsajkfhsakf','34'));
sys.puts(hashlib.hmac_sha1('wow','smsm'));
sys.puts(hashlib.hmac_sha1('HEY MAN','man man'));
sys.puts(hashlib.hmac_sha1('HEY MAN','man man2'));
