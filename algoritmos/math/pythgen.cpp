#define CC 100
void gen(int a = 3, int b = 4, int c = 5) {
	if(c > CC) return;
	printf("%d^2 + %d^2 = %d^2\n", a, b, c);
	gen( a - 2*b + 2*c,  2*a - b + 2*c,  2*a - 2*b + 3*c);
	gen( a + 2*b + 2*c,  2*a + b + 2*c,  2*a + 2*b + 3*c);
	gen(-a + 2*b + 2*c, -2*a + b + 2*c, -2*a + 2*b + 3*c);
}
