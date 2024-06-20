#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<int> vi;

ll lose(ll cur) {
    cur = cur * 9 / 10;
    cur = cur - cur % 25;
    return cur;
}

void ok() {
  cout << "biceps" << endl;
  exit(0);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  ll orig, today, days;
  cin >> orig >> today >> days;

  if (days >= 1000000000000000000LL / 25LL + 400) ok();
  
  // Try to zero out in the beginning.
  ll cur = orig;
  int mx = 0;
  for (int i = 1; i <= days; i++) {
    cur = lose(cur);
    if (cur == 0) {
      if (25 * (days - i) >= today) {
        ok();
      }
      break;
    }
  }

  for (int i = 0; i <= min(days, 400LL); i++) {
    ll lo = orig + (days - i) * 25;
    ll hi = orig;
    for (int j = 0; j < i; j++) {
      lo = lose(lo);
      hi = lose(hi);
    }
    hi += (days - i) * 25;
    if (lo <= today && today <= hi) {
      ok();
    }
  }
  cout << "liar" << endl;
}
