# Hashlib
*Is a FAST nodejs(http://github.com/ry/node/) library for making hashes written in C/C++*

*Supports: md4, md5, md6, sha, sha1, sha256, sha512*

## Install:
### way 1
1) go to the directory with hashlib library

2) execute `node-waf configure build`

3) get module from `./build/default/hashlib.node`

You should use `var hashlib = require("./build/default/hashlib");` (way to module)

### way 2 (works if node are installed in default path)
1) go to the directory with hashlib library

2) execute `make`

3) execute `sudo make install`

You should use `var hashlib = require("hashlib");` (from any path)

## Functions:
	md4([sting] str); // Returns md4 hash from sting
	md5([sting] str); // Returns md5 hash from sting
	sha([sting] str); // Returns sha hash from sting
	sha1([sting] str); // Returns sha1 hash from sting
	sha256([sting] str); // Returns sha256 hash from sting
	sha512([sting] str); // Returns sha512 hash from sting
	md6([sting] str, [int] length); // Returns md6 hash from sting, second parametr is optional
	
## Usage:
	var hashlib = require('hashlib');
	hashlib.md5('text');
	
## Speed testing
To run speed test on your computer run test.js, here is my:
	C++ md5 result is: 220
	JS md5 result is: 5660
	C++ module faster than JS in 25.727272727272727 times
	-----------
	C++ md4 result is: 212
	C++ md6 result is: 3889
	C++ sha0 result is: 228
	C++ sha1 result is: 495
	C++ sha256 result is: 712
	C++ sha512 result is: 612
	
	// Smaller is better

Other modules, engines md5 comparsion:
	hashlib: 220
	node-crypto: 1055
	python-hashlib: 265
	php: 179
	
	// Smaller is better

<img src="http://nodejs.ru/img/small.png">
