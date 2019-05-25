#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXM = 50'000;
typedef bitset<MAXM> B;

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

enum { ACQUIRE, RELEASE, ACCESS, CALL };

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N;
	cin >> N;
	map<string, int> fns, muts;
	auto lookup = [&](map<string, int>& m, const string& s) {
		int& r = m[s];
		if (!r) r = sz(m);
		return r-1;
	};
	int main = lookup(fns, "main");
	map<int, vector<pii>> fnv;
	rep(i,0,N) {
		int K;
		string name;
		cin >> K >> name;
		int namei = lookup(fns, name);
		vector<pii> instrs;
		rep(j,0,K) {
			string instr, x;
			cin >> instr >> x;
			if (instr == "acquire") instrs.emplace_back(ACQUIRE, lookup(muts, x));
			else if (instr == "release") instrs.emplace_back(RELEASE, lookup(muts, x));
			else if (instr == "access") instrs.emplace_back(ACCESS, lookup(muts, x));
			else if (instr == "call") instrs.emplace_back(CALL, lookup(fns, x));
			else assert(0);
		}
		fnv[namei] = move(instrs);
	}

	assert(sz(fnv) == N);
	vector<vector<pii>> bodies(N);
	rep(i,0,N) bodies[i] = move(fnv[i]);

	int M = sz(muts);
	assert(M <= MAXM);
	vector<B> zeroins(N), oneins(N), zeroouts(N), oneouts(N);
	vi error(N);

	vector<vi> gr(N);
	rep(i,0,N) trav(ins, bodies[i]) {
		if (ins.first == CALL) gr[i].push_back(ins.second);
	}
	vi ord = topo_sort(gr);
	reverse(all(ord));
	assert(sz(ord) == N);

	trav(i, ord) {
		B zeroin{}, onein{};
		B cur{}, known{};
		if (i == main) known.flip();
		bool err = false;
		trav(ins, bodies[i]) {
			int x = ins.second;
			if (ins.first == ACQUIRE) {
				if (!known[x]) {
					known[x] = 1;
					cur[x] = 1;
					zeroin[x] = 1;
				} else if (cur[x] == 1) {
					err = true;
				} else {
					cur[x] = 1;
				}
			}
			else if (ins.first == RELEASE) {
				if (!known[x]) {
					known[x] = 1;
					cur[x] = 0;
					onein[x] = 1;
				} else if (cur[x] == 0) {
					err = true;
				} else {
					cur[x] = 0;
				}
			}
			else if (ins.first == ACCESS) {
				if (!known[x]) {
					known[x] = 1;
					cur[x] = 1;
					onein[x] = 1;
				} else if (cur[x] == 0) {
					err = true;
				}
			}
			else {
				B zi = zeroins[x], oi = oneins[x];
				B zo = zeroouts[x], oo = oneouts[x];
				if (error[x] || (zi & cur).any() || (oi & ~cur & known).any()) {
					err = true;
				}
				else {
					zeroin |= ~known & zi;
					onein |= ~known & oi;
					known |= zo;
					known |= oo;
					cur |= oo;
					cur &= ~zo;
				}
			}
		}
		zeroins[i] = zeroin;
		oneins[i] = onein;
		zeroouts[i] = ~cur & known;
		oneouts[i] = cur;
		error[i] = err;
	}

	if (!error[main]) {
		cout << "a-ok" << endl;
	} else {
		cout << "deadlock" << endl;
	}
}
