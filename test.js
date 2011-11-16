var hashlib = require("./build/Release/hashlib");
var md5 = require("./test/md5");
var crypto = require("crypto");
var assert = require("assert");

process.chdir(__dirname);

if (hashlib.md5('test')=='098f6bcd4621d373cade4e832627b4f6')
	console.log('test 1 PASSED');
else
	console.log('test 1 FAILS');
if (hashlib.sha1('test')=='a94a8fe5ccb19ba61c4c0873d391e987982fbbd3')
	console.log('test 2 PASSED');
else
	console.log('test 2 FAILS');
if (hashlib.sha256('test')=='9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08')
	console.log('test 3 PASSED');
else
	console.log('test 3 FAILS');
if (hashlib.sha512('test')=='ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff')
	console.log('test 4 PASSED');
else
	console.log('test 4 FAILS');
if (hashlib.md6('test')=='e2e671a86f079441639ff18928092c6e')
	console.log('test 5 PASSED');
else
	console.log('test 5 FAILS');
if (hashlib.md6('test',40)=='27ea128154b4934ae2bd7f9dac53cf81da0002cc')
	console.log('test 6 PASSED');
else
	console.log('test 6 FAILS');
if (hashlib.md4('test')=='db346d691d7acc4dc2625db19f9e3f52')
	console.log('test 7 PASSED');
else
	console.log('test 7 FAILS');
if (hashlib.sha('test')=='f8d3b312442a67706057aeb45b983221afb4f035')
	console.log('test 8 PASSED');
else
	console.log('test 8 FAILS');

var COLL = [0x18, 0x00, 0x00, 0x00, 0x04, 0x30, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x30, 0x00, 0x8e, 0x03, 0x00, 0x00, 0x08, 0x31, 0x00, 0x01, 0x00, 0x00];

if (hashlib.sha256(new Buffer([18, 00, 00, 00, 04, 30, 00, 10, 00, 00, 00, 10, 30, 00, 0x8d, 03, 00, 00, 08, 31, 00, 01, 00, 00])) ===
    hashlib.sha256(new Buffer([18, 00, 00, 00, 04, 30, 00, 10, 00, 00, 00, 10, 30, 00, 0x8e, 03, 00, 00, 08, 31, 00, 01, 00, 00])))
  console.log('test 9 FAILS');
else
  console.log('test 9 PASSED');

if (hashlib.sha256(new Buffer(COLL)) !==
    '182edb820977e12de4de8b0ff835049d9b40ae8c700a3ab2f22bd44e22d85d9c'){
  console.log('test 10 FAILS');
} else {
  console.log('test 10 PASSED');
}

if (hashlib.hmac_sha1('what do ya want for nothing?', 'Jefe')=='effcdf6ae5eb2fa2d27416d5f184df9c259a7c79')
	console.log('test 11 PASSED');
else
	console.log('test 11 FAILS');
if (hashlib.hmac_md5('what do ya want for nothing?', 'Jefe')=='750c783e6ab0b503eaa86e310a5db738')
	console.log('test 12 PASSED');
else
	console.log('test 12 FAILS');

// End of tests

// C++ md5
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.md5('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
console.log('C++ (hashlib) md5 result is: '+c);

// Node Native
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
  h=crypto.createHash('md5').update('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i)).digest('hex');
}
var m2=new Date().getTime();
var cr=m2-m1;
console.log('C++ (crypto) md5 result is: '+cr);

// JS md5
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=md5.md5('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var js=m2-m1;
console.log('JS md5 result is: '+js);
console.log('-----------');

// C++ md4
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.md4('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
console.log('C++ md4 result is: '+(c));

// C++ md6
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.md6('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
console.log('C++ md6 result is: '+(c));

// C++ sha0
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.sha('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
console.log('C++ sha0 result is: '+(c));

// C++ sha1
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.sha1('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
console.log('C++ sha1 result is: '+(c));

// C++ sha256
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.sha256('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
console.log('C++ sha256 result is: '+(c));

// C++ sha512
var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.sha512('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
console.log('C++ sha512 result is: '+(c));
