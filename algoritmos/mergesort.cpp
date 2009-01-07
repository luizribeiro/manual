void merge(int a[], int aux[], int esq, int meio, int dir) {
	int i, esq_fim, n, aux_pos;

	esq_fim = meio - 1;
	aux_pos = esq;
	n = dir - esq + 1;

	while(esq <= esq_fim && meio <= dir)
		if(a[esq] <= a[meio])
			aux[aux_pos++] = a[esq++];
		else
			aux[aux_pos++] = a[meio++];

	while(esq <= esq_fim)
		aux[aux_pos++] = a[esq++];

	while(meio <= dir)
		aux[aux_pos++] = a[meio++];

	for(i = 0; i < n; i++) {
		a[dir] = aux[dir];
		dir--;
	}
}

void mergesort(int a[], int aux[], int esq, int dir) {
	int meio;

	if(dir > esq) {
		meio = (dir + esq) / 2;
		mergesort(a, aux, esq, meio);
		mergesort(a, aux, meio + 1, dir);
		merge(a, aux, esq, meio + 1, dir);
	}
}
