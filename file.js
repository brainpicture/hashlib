var hashlib = require("./build/default/hashlib");
var sys = require("sys");

// /home/brainfucker/Videos/Up.In.The.Air.2009.DVDSCR.XviD-CAMELOT/camelot-uita.avi

/*hashlib.md5_file('/home/brainfucker/Soft/Excel2007.exe',function(value) { // fbb2553fa048111256a62f788e0bf881
	sys.puts('RESULT: '+value);
});*/
var m1=new Date().getTime();
hashlib.md5_file('test.file',function(value) { // fbb2553fa048111256a62f788e0bf881
	sys.puts('RESULT test.file: '+value);
	var m2=new Date().getTime();
	var c=m2-m1;
	sys.puts('time: '+(c));
	hashlib.md5_file('test.js',function(value) { // fbb2553fa048111256a62f788e0bf881
      hashlib.md5_file('/home/brainfucker/Soft/Excel2007.exe',function(value) { // fbb2553fa048111256a62f788e0bf881
	      sys.puts('RESULT Excel2007.exe: '+value);
      });
	  sys.puts('RESULT test.js: '+value);
  });
});


//6800




/*
setInterval(function() {
	sys.puts('timer');
},500);
*/
