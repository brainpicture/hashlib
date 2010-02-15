var hashlib = require("./build/default/hashlib");
var sys = require("sys");
var md5 = require("./test/md5");

process.chdir(__dirname);

// TEST VECTORS 
// http://www.faqs.org/rfcs/rfc2202.html
//
// Official test vectors.. don't appear to be working. Unless there is another text encoding step.
// i.e. ascii to hex... or something
//

result = hashlib.hmac_sha1('Hi There', 8, '0x0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b', 20);
sys.puts(result);
sys.puts(sys.inspect(result));
