/* 0 <= d[i] < MAXIMO */
#define MAXIMO 1000

void countingsort(int d[], int n) {
	int *c = new int[MAXIMO];
	int i, j, k;

	/* inicializa a contagem */
	for(i = 0; i < MAXIMO; i++)
		c[i] = 0;

	/* contagem dos elementos */
	for(i = 0; i < n; i++)
		c[d[i]]++;

	/* armazena no array */
	for(i = j = 0; i < n; i++)
		for(k = 0; k < c[i]; k++)
			d[j++] = i;

	delete c;
}
