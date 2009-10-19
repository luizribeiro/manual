struct polyn {
	int n, a[NN];

	polyn() { n = 0, memset(a, 0, sizeof(a));  }
	polyn(int d) { n = d, memset(a, 0, sizeof(a)); }

	void clean() { /* remove zeros a esquerda */
		while(a[n] == 0 && n > 0) n--;
	}

	void simplify() { /* divide por x ateh nao poder mais */
		clean();
		if(!n) return;
		int i;
		for(i = 0; !a[i] && i <= n; i++);
		if(i) {
			n -= i;
			FORI(j, n) a[j] = a[j+i];
		}
	}

	polyn operator+(polyn p) const {
		polyn r(max(n,p.n));
		FORI(i, r.n) r.a[i] = a[i] + p.a[i];
		return r;
	}

	polyn operator-(polyn p) const {
		polyn r(max(n,p.n));
		FORI(i, r.n) r.a[i] = a[i] - p.a[i];
		return r;
	}

	polyn operator*(polyn p) const {
		polyn r(n+p.n);
		FORI(i, n) FORI(j, p.n) r.a[i+j] = a[i]*p.a[j];
		return r;
	}

	bool isroot(int x) const {
		int y = 0;
		if(!x) return !a[0];
		FORI(i, n) {
			y -= a[i];
			if(y % x) return false;
			y /= x;
		}
		return !y;
	}

	set<int> solveint() { /* resolve para raizes int, cuide com x = 0! */
		set<int> roots;
		for(int i = 1, m = abs(a[0]); i*i <= m; i++) {
			if(m % i) continue;
			if(isroot(i)) roots.insert(i);
			if(isroot(-i)) roots.insert(-i);
			if(isroot(m/i)) roots.insert(m/i);
			if(isroot(-m/i)) roots.insert(-m/i);
		}
		return roots;
	}
};
