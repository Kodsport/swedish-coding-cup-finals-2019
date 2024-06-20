#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N, K;
	cin >> N >> K;
	string str;
	cin >> str;

	vi onelb(N+1 + K, N);
	vi twolb(N+1 + K, N);
	int last1 = N, last2 = N;
	for (int i = N-1; i >= 0; i--) {
		if (str[i] == '1') last1 = i;
		if (str[i] == '2') last2 = i;
		onelb[i] = last1;
		twolb[i] = last2;
	}

	vector<pii> dp1(N+1), dp2(N+1);
	vi dp(N+1);
	dp1[N] = dp2[N] = pii(0, N);
	for (int i = N-1; i >= 0; i--) {
		rep(it,0,2) {
			int ik = min(i + K, N);
			int q = onelb[ik];
			int p = twolb[i];
			if (p >= ik) {
				dp1[i] = pii(dp[ik] + 1, i);
			}
			else {
				// if start at p:
				auto solve = [&](int p) {
					int pk = min(p + K, N);
					if (q < pk) {
						pii r = dp1[q];
						return r.first + 1 + (r.second > p);
					}
					else {
						return dp[pk] + 2;
					}
				};
				int res = solve(p);

				// if start at i-1 or earlier:
				auto works = [&](int pos) {
					int p = twolb[pos + K];
					return solve(p) == res - 1;
				};
				// lo works, hi doesn't
				int lo = i, hi = max(i - K, -1); // p - K also fine if p < ik
				while (hi + 1 < lo) {
					int mid = (lo + hi) / 2;
					if (works(mid)) lo = mid;
					else hi = mid;
				}
				dp1[i] = pii(res, lo);
			}

			swap(dp1, dp2);
			swap(onelb, twolb);
		}
		dp[i] = min(dp1[i].first, dp2[i].first);
	}
	cout << dp[0] << endl;
}
