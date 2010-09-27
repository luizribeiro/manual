char txt[NN];			// in
int len;				// in, strlen(txt)
int sa[NN], isa[NN];	// out
int v[NN], tv[NN], k;
bool cmp(int a, int b) { return v[a+k] < v[b+k]; }
void buildsa() {
	int i, j;
	memset(v, 0xff, sizeof(v));
	for(i = 0; i < len; i++) v[i] = txt[i], sa[i] = i;
	k = 0, sort(sa, sa+len, cmp);
	for(k = 1;; k *= 2) {
		bool f = false;
		for(i = 0; i < len; i=j) {
			for(j = i+1; j < len && v[sa[j]] == v[sa[i]]; j++);
			if(j > i+1) sort(sa+i, sa+j, cmp), f = true;
		}
		if(!f) break;
		tv[sa[0]] = 0;
		for(i = 1; i < len; i++)
			tv[sa[i]] = tv[sa[i-1]]
				+ (v[sa[i]] != v[sa[i-1]] || v[sa[i]+k] != v[sa[i-1]+k]);
		for(i = 0; i < len; i++) v[i] = tv[i];
	}
	for(i = 0; i < len; i++) isa[sa[i]] = i;
}

int lcp[NN];
void computelcp() {
	int i, j, l;
	for(l = i = 0; i < len; i++) if(isa[i]) {
		j = sa[isa[i]-1];
		while(txt[i+l] == txt[j+l]) l++;
		lcp[isa[i]] = l;
		if(l) l--;
	}
}
