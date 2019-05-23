#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, K;
string str;

map<tuple<int, int, int>, int> memo;
int solve(int at, int a, int b) {
	int& out = memo[make_tuple(at, a, b)];
	if (out) return out-1;
	if (at == N) {
		out = 1;
		return 0;
	}
	if (a == 0 && b == 0) {
		out = 2 + min(solve(at, a + K, b), solve(at, a, b + K));
		return out-1;
	}
	if (a == 0 && str[at] == '1') {
		out = 2 + solve(at, a + K, b);
		return out-1;
	}
	if (b == 0 && str[at] == '2') {
		out = 2 + solve(at, a, b + K);
		return out-1;
	}
	out = 1 + solve(at + 1, max(0, a - 1), max(0, b - 1));
	return out-1;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	cin >> N >> K;
	cin >> str;
	cout << solve(0, 0, 0) << endl;
}
