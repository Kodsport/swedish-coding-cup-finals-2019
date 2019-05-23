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
vi onelb, twolb;
vi memo;
ll work;
int solve(int start) {
	if (memo[start] != -1) return memo[start];
	int res = INT_MAX;
	rep(it,0,2) {
		int r = 1;
		int one = min(start + K, N), two = start;
		if (it) swap(one, two);
		while (one != two) {
			if (one < two) {
				int p = onelb[one];
				if (p < two) {
					r++;
					one = min(p + K, N);
				}
				else one = two;
			}
			else {
				int p = twolb[two];
				if (p < one) {
					r++;
					two = min(p + K, N);
				}
				else two = one;
			}
			work++;
		}
		r += solve(one);
		res = min(res, r);
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
	onelb.assign(N+1, N);
	twolb.assign(N+1, N);
	int one = N, two = N;
	for (int i = N-1; i >= 0; i--) {
		if (str[i] == '1') one = i;
		if (str[i] == '2') two = i;
		onelb[i] = one;
		twolb[i] = two;
	}
	memo.assign(N+1, -1);
	memo[N] = 0;
	cout << solve(0) << endl;

	int ndp = N - (int)count(all(memo), -1);
	cerr << "work factor: " << (double)work / ndp << ", required DPs: " << ndp / (double)N << endl;
}
