// O(sum of lengths * 26) hashing-based solution
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

struct chash {
	const uint64_t C = ll(2e18 * M_PI) + 71; // large odd number
	ll operator()(ull x) const {
		return __builtin_bswap64(x*C);
	}
};

H hashString(string& s) { H h{}; trav(c,s) h=h*C+c; return h; }

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
		trav(c, s) {
			if ('0' <= c && c <= '9') c = (char)('a' - 10 + (c - '0'));
		}
		strs.push_back(s);
		len += sz(s);
		maxlen = max(maxlen, sz(s));
	}

	__gnu_pbds::gp_hash_table<ull, int, chash> hashes({},{},{},{},{1<<16});
	// unordered_map<ull, int> hashes; hashes.reserve(len);
	trav(s, strs) {
		hashes[hashString(s).get()] = 1;
	}

	HashInterval hi(maxlen);
	trav(s, strs) {
		H h = hashString(s);
		int res = 0;
		rep(j,0,sz(s)) {
			H p = hi.pw[sz(s)-1 - j];
			H base = h - p * s[j];
			rep(c,'a'-10,'z'+1) {
				H variant = base + p * c;
				auto it = hashes.find(variant.get());
				res += (it != hashes.end());
			}
		}
		res -= sz(s);
		cout << res << '\n';
	}
}
