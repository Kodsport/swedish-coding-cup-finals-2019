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
  // Cannot have non-friend on the bus if K = 1
  if (K == 1) {
    cout << "0 0" << endl;
    return 0;
  }

  vi groups(N);
  rep(i,0,N) cin >> groups[i];

  // We cannot include any groups of size 1
  rep(i,0,sz(groups)) {
    if (groups[i] == 1) {
      swap(groups[i], groups.back());
      groups.pop_back();
      --i;
    }
  }
  N = (int)groups.size();
  int sum = accumulate(all(groups), 0);

  // If we have a number of friends not divisible by K, we need to remove enough to be
  // divisible by K
  multiset<int> sorted;
  rep(i,0,N) sorted.insert(groups[i]);
  while (sum % K) {
    auto it = --sorted.end();
    int group = *it;
    sorted.erase(it);
    group--;
    if (group) {
      sorted.insert(group);
    }
    --sum;

    // We may have created a 1-group doing this -- they need to be removed.
    if (sorted.size()) {
      if (*sorted.begin() == 1) {
        sorted.erase(sorted.begin());
        --sum;
      }
    }
  }

  // Now we can pack everyone left on buses greedily, unless the largest
  // group X fullfills
  // X > (sum - X) * (K - 1)
  // X > (K - 1)sum - (K - 1)X
  // XK > (K - 1)sum
  //
  // If we convert Y candies, we need to have that
  // (X - Y)K <= (K - 1)sum
  // So that
  // (X - Y) <= (K - 1)sum / K
  ll mxAfter = ((K - 1) * sum + K - 1) / K;
  ll newKind = max(0LL, *sorted.rbegin() - mxAfter);

  cout << sum / K << " " << newKind << endl;
}
