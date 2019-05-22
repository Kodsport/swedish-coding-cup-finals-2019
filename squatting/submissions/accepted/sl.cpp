// O(sum of lengths) hashing-based solution
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Arithmetic mod 2^64-1.
typedef uint64_t ull;
struct H {
	ull x; H(ull x=0) : x(x) {}
#define OP(O,A,B) H operator O(H o) { ull r = x; asm \
	(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
	OP(+,,"d"(o.x)) OP(*,"mul %1\n", "r"(o.x) : "rdx")
	H operator-(H o) { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3;
static const ull D = 1236182318541923ULL;

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}


namespace std {
template<>
struct hash<tuple<ull, ull, int, int>> {
ull operator()(tuple<ull, ull, int, int> t) const {
	auto a = get<0>(t);
	auto b = get<1>(t);
	auto c = get<2>(t);
	auto d = get<3>(t);
	return ((a * D + b) * D + c) * D + d;
}
};
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N;
	cin >> N;
	string s;
	vector<string> strs;
	rep(i,0,N) {
		cin >> s;
		strs.push_back(s);
	}

	unordered_map<tuple<ull, ull, int, int>, int> hashes;
	trav(s, strs) {
		HashInterval hi(s);
		rep(j,0,sz(s)) {
			ull a = hi.hashInterval(0, j).get();
			ull b = hi.hashInterval(j+1, sz(s)).get();
			int c = sz(s);
			int d = j;
			hashes[make_tuple(a, b, c, d)]++;
		}
	}

	trav(s, strs) {
		int res = 0;
		HashInterval hi(s);
		rep(j,0,sz(s)) {
			ull a = hi.hashInterval(0, j).get();
			ull b = hi.hashInterval(j+1, sz(s)).get();
			int c = sz(s);
			int d = j;
			res += hashes[make_tuple(a, b, c, d)];
		}
		res -= sz(s);
		cout << res << '\n';
	}
}
