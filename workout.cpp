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

  ll N, M;
  cin >> N >> M;
  set<pii> Q;
  Q.insert(pii(N, N));
  rep(i,0,M) {
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
    cout << Q.size() << endl;
  }
}
