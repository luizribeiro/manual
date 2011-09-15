template <typename _T>
vector<_T> lis(vector<_T>& seq){
	int i, m, n = seq.size(), u, tail = 0,  v;
	if (n < 1) return vector<_T>();
	vector<int> p(n, -1);
	vector<_T> ret(1, 0);
	for (i = 1; i < n; i++) {
		if(seq[ret[tail]] < seq[i]){ // simply extend sequence
			p[i] = ret[tail++];
			ret.push_back(i);
			continue;
		}
		// binary search for best position to insert current element
		for (m = tail >> 1, u = 0, v = tail; u < v; m = (u + v) >> 1) 
			if (seq[ret[m]] < seq[i]) u = m + 1;
			else v = m;
		if (seq[i] < seq[ret[u]]) {
			if(u) p[i] = ret[u - 1];
			ret[u] = i;
		}	
	}
	for(u = tail + 1, v = ret[tail]; u--; v = p[v]) ret[u] = seq[v];
	return ret;
}

