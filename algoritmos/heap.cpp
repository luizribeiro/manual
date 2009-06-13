#define MAX_ELEM 1024

#define pai(i) (((i)-1)/2)
#define esq(i) (2*(i)+1)
#define dir(i) (2*(i)+2)

double h[MAX_ELEM];		/* heap (de maximo) */
int hn;					/* numero de elementos */

void sobe(int i) {
	if(i > 0 && h[i] > h[pai(i)]) {
		double t = h[pai(i)];
		h[pai(i)] = h[i];
		h[i] = t;
		sobe(pai(i));
	}
}

void desce(int i) {
	int filho;

	if(dir(i) < hn && h[dir(i)] > h[esq(i)])
		filho = dir(i);
	else
		filho = esq(i);

	if(filho < hn && h[filho] > h[i]) {
		double t = h[filho];
		h[filho] = h[i];
		h[i] = t;
		desce(filho);
	}
}

double pop() {
	double r = h[0];
	h[0] = h[--hn];
	desce(0);
	return r;
}

void push(double v) {
	h[hn] = v;
	sobe(hn++);
}
