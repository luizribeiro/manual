const int FF = 80000;
int ftree[FF];

int read(int idx) {
	int sum = 0;
	for(int i = idx; i; i -= (i & -i))
		sum += ftree[i];
	return sum;
}

void update(int idx, int val) {
	for(int i = idx; i < FF; i += (i & -i))
		ftree[i] += val;
}
