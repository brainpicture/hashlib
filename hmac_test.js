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

// sys.debug("TEST:1")
// result = hashlib.hmac_sha1('Hi There', '0x0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b');
// sys.puts(result);
// sys.puts(sys.inspect(result));
// sys.puts("SHOULD EQUAL: 0xb617318655057264e28bc0b6fb378c8ef146be00")


sys.debug("TEST:2")
result = hashlib.hmac_sha1('what do ya want for nothing?', 'Jefe');
sys.puts(result);
sys.puts(sys.inspect(result));
sys.puts("SHOULD EQUAL: effcdf6ae5eb2fa2d27416d5f184df9c259a7c79")
