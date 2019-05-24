#include <bits/stdc++.h>
using namespace std;

#include "validator.h"

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXM = 500'000;
typedef bitset<MAXM> B;

enum { ACQUIRE, RELEASE, ACCESS, CALL };

double unif(double lo, double hi) {
	return lo + rand() / (RAND_MAX + 1.0) * (hi - lo);
}

string rand_name() {
	int le = 8 + rand() % 3;
	string ret;
	rep(i,0,le) {
		ret += (char)('a' + rand() % 26);
	}
	return ret;
}

vi gen_tree(int n, string mode) {
	enum { RANDOM, STAR, LINE, SHALLOW, DEEP, DEEPER } imode;
	if (mode == "random") imode = RANDOM;
	else if (mode == "star") imode = STAR;
	else if (mode == "line") imode = LINE;
	else if (mode == "shallow") imode = SHALLOW;
	else if (mode == "deep") imode = DEEP;
	else if (mode == "deeper") imode = DEEPER;
	else assert(0);
	vi pars(n, -1);
	vi depth(1, 0);
	rep(i,1,n) {
		int pred;
		switch (imode) {
		case RANDOM:
            pred = rand() % i;
			break;
		case STAR:
			pred = 0;
			break;
		case LINE:
			pred = i-1;
			break;
		case SHALLOW:
            pred = (int)pow(unif(0, pow(i, 0.2)), 5);
			break;
		case DEEP:
            pred = i-1 - (int)pow(unif(0, pow(i, 0.1)), 10);
			break;
		case DEEPER:
            if (i < 4) {
                pred = rand() % i;
			}
            else {
                double hi = log2(log2(i));
                pred = i - (int) pow(2, pow(2, min({unif(-3, hi), unif(-3, hi), unif(-3, hi)})));
			}
			break;
		default:
            assert(false);
		}
        assert(0 <= pred && pred < i);
        pars[i] = pred;
        depth.push_back(depth[pred] + 1);
	}
	cerr << "max depth = " << *max_element(all(depth)) << endl;
    return pars;
}

void run() {
	SetGeneratorMode();
	int N = Arg("n");
	int L = Arg("l");
	int onek = Arg("k", 0);
	int tryk = Arg("tryk");
	int eachlo = Arg("eachlo");
	int eachhi = Arg("eachhi");
	int max_types = (int)Arg("onlyacq", 0) == 0 ? 3 : 1;
	string treemode = Arg("tree", "random");
	int extraEdges = Arg("calls");
	int error = Arg("error");

	int instrs = 0;
	vi pars = gen_tree(N, treemode);
	vector<vector<pii>> bodies(N);
	rep(i,1,N) {
		bodies[pars[i]].push_back({CALL, i});
		instrs++;
	}
	rep(i,0,extraEdges) {
		int b = rand() % (N - 1) + 1;
		int a = rand() % b;
		bodies[a].push_back({CALL, b});
		instrs++;
	}

	assert(instrs <= L);

	rep(t,0,tryk) {
		int e = rand() % (eachhi - eachlo + 1) + eachlo;
		rep(j,0,e) {
			int tp = rand() % max_types;
			int a = rand() % N;
			bodies[a].push_back({tp, t});
		}
	}

	rep(i,0,N) random_shuffle(all(bodies[i]));
	int main = 0;

	// Limit to 4GB of RAM usage
	assert(N <= 15000);
	assert(tryk <= MAXM);
	vector<B> zeroins(N), oneins(N), zeroouts(N), oneouts(N);
	vector<B> errors(N);

	for (int i = N-1; i >= 0; i--) {
		B zeroin{}, onein{};
		B cur{}, known{};
		if (i == main) known.flip();
		B error{};
		trav(ins, bodies[i]) {
			int x = ins.second;
			if (ins.first == ACQUIRE) {
				if (!known[x]) {
					known[x] = 1;
					cur[x] = 1;
					zeroin[x] = 1;
				} else if (cur[x] == 1) {
					error[x] = 1;
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
					error[x] = 1;
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
					error[x] = 1;
				}
			}
			else {
				B zi = zeroins[x], oi = oneins[x];
				B zo = zeroouts[x], oo = oneouts[x];
				error |= errors[x];
				error |= zi & cur;
				error |= oi & ~cur & known;
				zeroin |= ~known & zi;
				onein |= ~known & oi;
				known |= zo;
				known |= oo;
				cur |= oo;
				cur &= ~zo;
			}
		}
		zeroins[i] = zeroin;
		oneins[i] = onein;
		zeroouts[i] = ~cur & known;
		oneouts[i] = cur;
		errors[i] = error;

		// cerr << i << endl;
		// cerr << zeroins[i] << endl;
	}

	B err = errors[main];

	// Let some errors slip through
	rep(i,0,tryk) {
		if (!error) break;
		if (err[i]) {
			error--;
			err[i] = 0;
		}
	}

	instrs = 0;
	vi instrCount(tryk);
	rep(i,0,N) {
		vector<pii> nb;
		trav(is, bodies[i]) {
			if (is.first == CALL) instrs++;
			if (is.first != CALL && !err[is.second]) {
				instrCount[is.second]++;
				instrs++;
			}
		}
	}

	int origInstrs = instrs;
	while (instrs > L) {
		tryk--;
		instrs -= instrCount[tryk];
	}

	if (onek) {
		int firstNonErr = 0;
		while (firstNonErr < tryk && instrCount[firstNonErr] == 0)
			firstNonErr++;
		if (firstNonErr != tryk)
			tryk = firstNonErr + 1;
	}

	instrs = 0;
	rep(i,0,N) {
		vector<pii> nb;
		trav(is, bodies[i]) {
			if (is.first == CALL || (!err[is.second] && is.second < tryk))
				nb.push_back(is);
		}
		bodies[i] = move(nb);
		instrs += sz(bodies[i]);
	}

	cerr << "Failures: " << err.count() << '/' << tryk
		<< ", instrs: " << origInstrs << '/' << L
		<< ", reduced to " << instrs << endl;

	vi order(N);
	iota(all(order), 0);
	random_shuffle(all(order));
	vector<string> names(N);
	names[0] = "main";
	rep(i,1,N) names[i] = rand_name();
	vector<string> mutNames(tryk);
	rep(i,0,tryk) mutNames[i] = rand_name();

	cout << N << endl;
	const char *insNames[4] = {"acquire", "release", "access", "call"};
	trav(i, order) {
		cout << sz(bodies[i]) << ' ' << names[i] << endl;
		trav(ins, bodies[i]) {
			cout << insNames[ins.first] << ' ';
			if (ins.first == CALL) cout << names[ins.second];
			else cout << mutNames[ins.second];
			cout << endl;
		}
	}
}
