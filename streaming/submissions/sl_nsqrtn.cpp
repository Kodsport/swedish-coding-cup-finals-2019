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

vi memo;
int solve(int start) {
	if (memo[start] != -1) return memo[start];
	int res = INT_MAX;
	rep(it,0,2) {
		int r = 1;
		int one = min(start + K, N), two = start;
		if (it) swap(one, two);
		int i = start;
		for (; i < one || i < two; i++) {
			char c = str[i];
			if (c == '1' && i >= one) {
				r++;
				one = min(i + K, N);
			}
			if (c == '2' && i >= two) {
				r++;
				two = min(i + K, N);
			}
		}
		r += solve(i);
		res = min(res, r);
	}
	memo[start] = res;
	return res;
}

vector<vi> memo2[2];
int solve_nk(int at, int b, int side) {
	int& out = memo2[side][b][at];
	if (out != -1) return out;
	if (at == N) {
		return out = 0;
	}
	if (b == 0) {
		return out = 1 + min(solve_nk(at, K, side), solve_nk(at, K, !side));
	}
	if (str[at] == '1' + side) {
		return out = 1 + solve_nk(min(at + b, N), K - b, !side);
	}
	return out = solve_nk(at + 1, b - 1, side);
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	cin >> N >> K;
	cin >> str;
	assert(sz(str) == N);
	if (K > 200) {
		memo.assign(N+1, -1);
		memo[N] = 0;
		cout << solve(0) << endl;
	} else {
		memo2[0].assign(K+1, vi(N+1, -1));
		memo2[1].assign(K+1, vi(N+1, -1));
		cout << solve_nk(0, 0, 0) << endl;
	}
}
