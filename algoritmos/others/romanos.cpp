string decimal2roman(int n) {
	const string rom[13] = {  "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
	const int dec[13] =    { 1000,  900, 500,  400, 100,   90,  50,   40,  10,   9,    5,    4,   1 };
	string ret = "";
	for(int i = 0; i < 13; i++) {
		while(n >= dec[i]) {
			n -= dec[i];
			ret += rom[i];
		}
	}
	return ret;
}
