void bubblesort(int d[], int n)  {
	int i, j, k = n - 1;
	int t;

	for(i = 0; i < n; i++, k--) {
		for(j = 0; j < k; j++) {
			if(d[j] > d[j+1]) {
				t = d[j];
				d[j] = d[j+1];
				d[j+1] = t;
			}
		}
	}
}

