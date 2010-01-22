var hashlib = require("./build/default/hashlib");
var sys = require("sys");

// /home/brainfucker/Videos/Up.In.The.Air.2009.DVDSCR.XviD-CAMELOT/camelot-uita.avi

/*hashlib.md5_file('/home/brainfucker/Soft/Excel2007.exe',function(value) { // fbb2553fa048111256a62f788e0bf881
	sys.puts('RESULT: '+value);
});*/

hashlib.md5_file('./test.file',function(value) { // fbb2553fa048111256a62f788e0bf881
	sys.puts('RESULT: '+value);
});




/*
setInterval(function() {
	sys.puts('timer');
},500);
*/
