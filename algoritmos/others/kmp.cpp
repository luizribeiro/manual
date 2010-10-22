char K[KKL], W[WWL];	// chave de busca, texto
int F[KKL];				// tabela de falhas

void kmp_table(char *K, int KL){
	F[0] = F[1] = 0;
	int i, j;
	for(i = 2; i < KL; ++i){
		j = F[i - 1];
		while(1){
			if(K[j] == K[i - 1]){ F[i] = j + 1; break; }
			if(j == 0){ F[i] = 0; break; }
			j = F[j];
		}
	}
}

int kmp(char *W, int WL, char *K, int KL){
	kmp_table(K, KL);
	for(int i = 0, j = 0; j < WL; ){
		if(W[j] == K[i]){
			i++;
			j++;
			if(i == KL) return j;
		} else if(i > 0) i = F[i];
		else j++;
	}
	return -1;
}
