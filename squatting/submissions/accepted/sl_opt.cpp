// O(sum of lengths) hashing-based solution
#include <bits/extc++.h>
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
	HashInterval(int maxlen) {
		pw.resize(maxlen + 1);
		pw[0] = 1;
		rep(i,0,maxlen)
			pw[i+1] = pw[i] * C;
	}
	void reset(string& str) {
		ha.resize(sz(str) + 1);
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i];
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
struct hash<tuple<ull, ull, ull>> {
ull operator()(tuple<ull, ull, ull> t) const {
	auto a = get<0>(t);
	auto b = get<1>(t);
	auto c = get<2>(t);
	return (a * D + b) * D + c;
}
};
}

ull hashTuple(tuple<ull,ull,ull> x) {
	const uint64_t C = ll(2e18 * M_PI) + 71;
	ull h = get<0>(x);
	h *= C;
	h ^= get<1>(x);
	h *= C;
	h ^= get<2>(x);
	return h;
}

struct chash {
	const uint64_t C = ll(2e18 * M_PI) + 71; // large odd number
	ll operator()(ull h) const {
		return __builtin_bswap64(h*C);
	}
};

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N;
	cin >> N;
	string s;
	vector<string> strs;
	int len = 0;
	int maxlen = 0;
	rep(i,0,N) {
		cin >> s;
		strs.push_back(s);
		len += sz(s);
		maxlen = max(maxlen, sz(s));
	}

	__gnu_pbds::gp_hash_table<ull, int, chash> hashes({},{},{},{},{1<<20});
	// unordered_map<tuple<ull, ull, ull>, int> hashes; hashes.reserve(len);
	HashInterval hi(maxlen);
	trav(s, strs) {
		hi.reset(s);
		rep(j,0,sz(s)) {
			ull a = hi.hashInterval(0, j).get();
			ull b = hi.hashInterval(j+1, sz(s)).get();
			ull c = (ull)sz(s) << 32 | j;
			hashes[hashTuple(make_tuple(a, b, c))]++;
		}
	}

	trav(s, strs) {
		int res = 0;
		hi.reset(s);
		rep(j,0,sz(s)) {
			ull a = hi.hashInterval(0, j).get();
			ull b = hi.hashInterval(j+1, sz(s)).get();
			ull c = (ull)sz(s) << 32 | j;
			res += hashes[hashTuple(make_tuple(a, b, c))];
		}
		res -= sz(s);
		cout << res << '\n';
	}
}
