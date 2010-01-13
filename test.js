var hashlib = require("./build/default/hashlib");
var sys = require("sys");

sys.puts(hashlib.md5([2,4,6]));
var md5 = require("./lib/md5");

var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=hashlib.md5('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var c=m2-m1;
sys.puts('C++ module result is: '+(c));

var m1=new Date().getTime();
for(i=0;i<100000;i++) {
	h=md5.md5('EdPy2H71Q1MjTzkuRxAr1CJWs2ZapZEuaY3XwJL8mpxaTBLWZPkw1yakKLv2r79eHmNQ1m2Cc6PErAkH5FR3Nmd011F09LCas76Z'+String(i));
}
var m2=new Date().getTime();
var js=m2-m1;
sys.puts('JS module result is: '+(js));

if (c<js) sys.puts('C module faster than JS in '+(js/c)+' times');
else if (c>js) sys.puts('JS module faster than C in '+(c/j)+' times');
