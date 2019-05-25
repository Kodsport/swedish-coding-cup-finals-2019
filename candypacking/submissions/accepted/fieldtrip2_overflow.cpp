#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  vi groups(N);
  rep(i,0,N) cin >> groups[i];
  sort(all(groups));

  ll sum = accumulate(all(groups), 0);
  if (sum / K == 0) {
    cout << "0 0" << endl;
  } else if (sum / K == 1) {
    int rem = 0;
    int left = K;
    trav(it, groups) {
      left -= max(1, it - 1);
    }
    trav(it, groups) {
      if (left <= 0) break;
      if (it == 1) continue;
      left--;
      rem += it - 1;
    }
    cout << 1 << " " << rem << endl;
  } else {
    ll remove = sum % K;
    ll mx = groups.back();
    
    mx -= remove;
    sum -= remove;

    // OK if (mx - Y) <= (sum - mx + Y) * (K - 1)
    // (mx - Y) * (1 + K -1) <= sum * (K - 1)
    // (mx - Y) * K <= sum * (K - 1)
    // mx * K - sum * (K - 1) <= YK
    // mx - sum * (K - 1) / K <= Y
    ll changes = max(0LL, mx - sum * (K - 1) / K);
    cout << sum / K << " " << changes << endl;
  }
}
