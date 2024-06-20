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
vector<vi> memo[2];
int solve(int at, int b, int side) {
	return memo[side][at][b];
}

int rsolve(int at, int b, int side) {
	if (at == N) {
		return 0;
	}
	if (b == 0) {
		return 1 + min(solve(at, K, side), solve(at, K, !side));
	}
	if (str[at] == '1' + side) {
		return 1 + solve(min(at + b, N), K - b, !side);
	}
	return solve(at + 1, b - 1, side);
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	cin >> N >> K;
	cin >> str;
	assert(sz(str) == N);
	memo[0].assign(N+1, vi(K+1, -1));
	memo[1].assign(N+1, vi(K+1, -1));
	for (int at = N; at >= 0; at--) {
		for (int b = K; b >= 0; b--) {
			rep(side,0,2)
				memo[side][at][b] = rsolve(at, b, side);
		}
	}
	cout << solve(0, 0, 0) << endl;
}
