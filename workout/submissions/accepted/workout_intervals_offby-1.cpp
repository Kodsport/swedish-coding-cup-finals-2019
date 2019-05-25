#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<int> vi;

pii win(const pii& cur) {
  return pii(cur.first + 25, cur.second + 25);
}

ll fail(ll cur) {
  ll fail = cur * 9 / 10;
  return fail - (fail % 25);
}

pii lose(const pii& cur) {
  return pii(fail(cur.first), fail(cur.second));
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  ll orig, today, days;
  cin >> orig >> today >> days;
  set<pii> Q;
  Q.insert(pii(orig, orig));
  rep(i,0,days) {
    set<pii> NQ;
    trav(it, Q) {
      NQ.insert(win(it));
      NQ.insert(lose(it));
    }
    Q.clear();
    pii cur = *NQ.begin();
    trav(it, NQ) {
      if (it.first - 25 <= cur.second) {
        cur.second = max(it.second, cur.second);
      } else {
        Q.insert(cur);
        cur = it;
      }
    }
    Q.insert(cur);
  }
  auto it = Q.lower_bound(pii(today + 1, 0));
  if (it != Q.begin()) {
    --it;
  }
  today++;
  if (it->first <= today && today <= it->second) {
    cout << "biceps" << endl;
  } else {
    cout << "liar" << endl;
  }
}
