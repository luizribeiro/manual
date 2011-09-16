struct trie {
	struct node {
		int edges[26];
		vector<int> output; // set of patterns of the state
		int f; // failure function
		node() {
			f = 0;
			for(int i = 0; i < 26; i++)
				 edges[i] = -1;
		}
	};

	vector<node> nodes;

	trie() { nodes.push_back(node()); }
	trie(vector<string> dict);
	int insert(string str);
	void build(void);
};

trie::trie(vector<string> dict) {
	nodes.push_back(node()); // creates root
	for(int i = 0; i < (int)dict.size(); i++) {
		int x = insert(dict[i]);
		nodes[x].output.push_back(i);
	}
	build();
}

int trie::insert(string str) {
	int n = 0;
	for(int i = 0; i < (int)str.size(); i++) {
		if(nodes[n].edges[str[i]-'a'] == -1) {
			nodes[n].edges[str[i]-'a'] = nodes.size();
			nodes.push_back(node());
		}
		n = nodes[n].edges[str[i]-'a'];
	}
	return n;
}

// builds the Aho-Corasick automata
void trie::build(void) {
	// complete the goto function for the root
	for(int i = 0; i < 26; i++)
		if(nodes[0].edges[i] == -1)
			nodes[0].edges[i] = 0;

	queue<int> q;
	for(int i = 0; i < 26; i++)
		if(nodes[0].edges[i] != 0)
			q.push(nodes[0].edges[i]);
	while(!q.empty()) {
		int n = q.front(); q.pop();
		for(int i = 0; i < 26; i++) {
			int u = nodes[n].edges[i];
			if(u > 0) {
				int v = nodes[n].f;
				while(nodes[v].edges[i] == -1)
					v = nodes[v].f;
				nodes[u].f = nodes[v].edges[i];
				q.push(u);
			}
		}
	}
}

void ahocorasick(string str, trie dict) {
	int i = 0; // AC automata state
	for(int j = 0; j < (int)str.size(); j++) {
		int ch = str[j]-'a';
		while(dict.nodes[i].edges[ch] == -1)
			i = dict.nodes[i].f; // follow a fail
		i = dict.nodes[i].edges[ch]; // follow a goto
		if(dict.nodes[i].output.size()) {
			for(int v = i; v; v = dict.nodes[v].f)
				for(int k = 0; k < (int)dict.nodes[v].output.size(); k++)
					printf("found a match of string %d ending at index %d\n", dict.nodes[v].output[k], j);
		}
	}
}
