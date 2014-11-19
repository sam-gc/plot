var funccount = process.argv[2];
var start = parseFloat(process.argv[3]);
var end = parseFloat(process.argv[4]);
var count = parseInt(process.argv[5]);

for(var f = 0; f < funccount; f++) {
	var func = process.argv[f + 6];

	for(var i = 0; i < count; i++) {
		step = (end - start) / count;
		var x = i * step + start;
		var v = 'x';

		var parts = func.split('|');
		if(parts.length > 1)
			v = parts[1];

		var reg = new RegExp(v, "g");
		var str = parts[0].replace(reg, x);
		console.log(eval(str));
	}
}