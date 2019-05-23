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
ll work;
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
		work += i - start;
	}
	memo[start] = res;
	return res;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	cin >> N >> K;
	cin >> str;
	assert(sz(str) == N);
	memo.assign(N+1, -1);
	memo[N] = 0;
	cout << solve(0) << endl;

	int ndp = N - (int)count(all(memo), -1);
	cerr << "work factor: " << (double)work / ndp << ", required DPs: " << ndp / (double)N << endl;
}
