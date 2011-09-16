/*
   luizribeiro's topcoder library
   misc.cpp
*/

/* Decimal to Roman Numerical System {{{ */
string decimal2roman(int n) {
	const string rom[13] = {  "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
	const int dec[13] =    { 1000,  900, 500,  400, 100,   90,  50,   40,  10,   9,    5,    4,   1 };
	string ret = "";
	for(int i = 0; i < 13; i++) {
		while(n >= dec[i]) {
			n -= dec[i];
			ret += rom[i];
		}
	}
	return ret;
}
/* }}} */

/* Knuth-Morris-Pratt {{{ */
char text[TT], patt[PP]; // text, pattern
int n, m; // strlen(text), strlen(pattern)
int f[PP]; // failure table

void buildf(void) {
	f[0] = f[1] = 0;
	for(int i = 2; i <= m; i++) {
		f[i] = -1;
		for(int j = f[i-1]; f[i] == -1; j = f[j])
			if(patt[j] == patt[i-1]) f[i] = j+1;
			else if(j == 0) f[i] = 0;
	}
}

void kmp(void) {
	buildf();
	for(int i = 0, j = 0; j < n; j++) {
		// i = automaton's state, j = text position
		if(text[j] == patt[i]) {
			i++; // move to next state
			if(i == m) {
				printf("found match at index %d\n", j-m+1);
				i = f[i];
			}
		} else if(i) i = f[i], j--;
	}
}
/* }}} */

/* KMP's properties {{{

if(f[i] > 0 && (i % (i - f[i])) == 0)
	prefix with size i is periodic, with period length = (i - f[i])

}}} */

/* KMP 2D {{{ */
char text[TT][TT], patt[PP][PP]; // text, pattern [row][col]
int n1, n2; // num of rows, cols patt
int m1, m2; // num of rows, cols text
int f[PP]; // failure table

void buildf(void) {
	f[0] = f[1] = 0;
	for(int i = 2; i <= n1; i++) {
		f[i] = -1;
		for(int j = f[i-1]; f[i] == -1; j = f[j])
			if(strcmp(patt[j], patt[i-1]) == 0) f[i] = j+1;
			else if(j == 0) f[i] = 0;
	}
}

void kmp(void) {
	buildf();
	for(int k = 0; k <= m2-n2; k++) {
		for(int i = 0, j = 0; j < m1; j++) {
			// i = automaton's state, j = text position
			if(strncmp(text[j]+k, patt[i], n2) == 0) {
				i++;
				if(i == n1) {
					printf("found match at (%d, %d)\n", j-n1+2, k+1);
					i = f[i];
				}
			} else if(i) i = f[i], j--;
		}
	}
}
/* }}} */

/* Aho-Corasick {{{ */
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
/* }}} */

/* Alpha Beta {{{ */
function alphabeta(node, depth, α, β, Player)
	if depth = 0 or node is a terminal node
		return the heuristic value of node
	if Player = MaxPlayer
		for each child of node
			α := max(α, alphabeta(child, depth-1, α, β, not(Player)))
			if β ≤ α
				break                             (* Beta cut-off *)
		return α
	else
		for each child of node
			β := min(β, alphabeta(child, depth-1, α, β, not(Player)))
			if β ≤ α
				break                             (* Alpha cut-off *)
		return β
(* Initial call *)
alphabeta(origin, depth, -infinity, +infinity, MaxPlayer)
/* }}} */
