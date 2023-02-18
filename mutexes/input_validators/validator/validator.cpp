#include "validator.h"
#include <queue>
using namespace std;

string token(char sep) {
	string str;
	for (;;) {
		char c = Char();
		if (c == sep) break;
		assert('a' <= c && c <= 'z');
		str += c;
	}
	return str;
}

// From KACTL
typedef vector<int> vi;
#define trav(a, x) for (auto& a : x)
#define rep(i,f,t) for (int i = f; i < (t); i++)
#define sz(x) (int)(x).size()
vi topo_sort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	trav(li, gr) trav(x, li) indeg[x]++;
	queue<int> q; // use priority queue for lexic. smallest ans.
	rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(-i);
	while (!q.empty()) {
		int i = -q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		trav(x, gr[i])
			if (--indeg[x] == 0) q.push(-x);
	}
	return ret;
}

void run() {
	int L = Arg("l");
	int K = Arg("k", L);
	int onlyAcq = Arg("onlyacq", 0);
	int n = Int(1, L);
	set<string> mutexes;
	Endl();
	long long count = 0;
	vector<vector<string>> eds1;
	map<string, int> fnames;
	for (int i = 0; i < n; i++) {
		int instr = Int(0, L);
		Space();
		string fname = token('\n');
		fnames[fname] = i;
		count += instr;
		assert(count <= L);
		vector<string> calls;
		for (int j = 0; j < instr; j++) {
			string ins = token(' ');
			string name = token('\n');
			if (ins == "release" || ins == "acquire" || ins == "access") {
				mutexes.insert(name);
				if (onlyAcq) {
					assert(ins == "acquire");
				}
			} else if (ins == "call") {
				calls.push_back(name);
			} else {
				die("invalid instruction " + ins);
			}
		}
		eds1.push_back(move(calls));
	}

	assert(sz(mutexes) <= K);
	assert(sz(mutexes) >= 1); // sanity

	// Resolve function names
	assert(fnames.count("main"));
	assert(sz(fnames) == n);
	vector<vector<int>> eds;
	for (int i = 0; i < n; i++) {
		vector<int> adj;
		for (string& s : eds1[i]) {
			adj.push_back(fnames[s]);
		}
		eds.push_back(move(adj));
	}
	assert(sz(fnames) == n);

	// No cycles
	assert(sz(topo_sort(eds)) == n);
}
