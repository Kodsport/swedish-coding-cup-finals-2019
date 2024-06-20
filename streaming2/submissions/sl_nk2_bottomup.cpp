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

int memo[500001][11][11];
int solve(int at, int a, int b) {
	return memo[at][a][b];
}

int dosolve(int at, int a, int b) {
	if (at == N) {
		return 0;
	}
	if (a == 0 && b == 0) {
		return 1 + min(solve(at, a + K, b), solve(at, a, b + K));
	}
	if (a == 0 && str[at] == '1') {
		return 1 + solve(at, a + K, b);
	}
	if (b == 0 && str[at] == '2') {
		return 1 + solve(at, a, b + K);
	}
	return solve(at + 1, max(0, a - 1), max(0, b - 1));
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	cin >> N >> K;
	assert(N <= 500000);
	assert(K <= 10);
	cin >> str;
	for (int at = N; at >= 0; at--)
	for (int a = K; a >= 0; a--)
	for (int b = K; b >= 0; b--) {
		memo[at][a][b] = dosolve(at, a, b);
	}
	cout << solve(0, 0, 0) << endl;
}
