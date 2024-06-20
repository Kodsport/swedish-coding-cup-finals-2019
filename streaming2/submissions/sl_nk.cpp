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
	int& out = memo[side][b][at];
	if (out != -1) return out;
	if (at == N) {
		return out = 0;
	}
	if (b == 0) {
		return out = 1 + min(solve(at, K, side), solve(at, K, !side));
	}
	if (str[at] == '1' + side) {
		return out = 1 + solve(min(at + b, N), K - b, !side);
	}
	return out = solve(at + 1, b - 1, side);
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	cin >> N >> K;
	cin >> str;
	assert(sz(str) == N);
	memo[0].assign(K+1, vi(N+1, -1));
	memo[1].assign(K+1, vi(N+1, -1));
	cout << solve(0, 0, 0) << endl;
}
