#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int fnid(const string& s, const map<string, int>& fns) {
    auto it = fns.find(s);
    if (it != fns.end()) return it->second;
    int w = fns.size();
    return fns[s] = w;
}

struct Op { int call; int acq; int rel; int acc; };

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

  map<string, int> fns, mutexes;
  vector<int> outdeg;

  int N;
  cin >> N;

  vector<vector<Op>> ops(N);
  vector<vi> eds(N);

  rep(i,0,N) {
    int M;
    string X;
    cin >> M >> X;
    int funcid = fnid(X, fns);

    rep(j,0,M) {
      string cmd;
      cin >> cmd;

      if (cmd == "acquire") {
        string mutex; cin >> mutex;
        ops[funcid].emplace_back(-1, fnid(mutex, mutexes), -1. -1);
      } else if (cmd == "release") {
        string mutex; cin >> mutex;
        ops[funcid].emplace_back(-1, -1, fnid(mutex, mutexes), -1);
      } else if (cmd == "access") {
        string mutex; cin >> mutex;
        ops[funcid].emplace_back(-1, -1, -1, fnid(mutex, mutexes));
      } else {
        string fn;
        cin >> fn;
        int funcid2 = fnid(X, fns);
        eds[funcid2].push_back(funcid);
        outdeg[funcid]++;
        ops[funcid].emplace_back(funcid2, -1, -1, -1);
      }
    }
  }
  eds.resize(sz(fns));
  trav(it, teds) {
    eds[it.first].push_back(it.second);
    outdeg[it.first]++;
  }

  vector<int> ord;
  queue<int> q;
  rep(i,0,N) if (outdeg[i] == 0) q.push(i);
  while (!q.empty()) {
    int x = q.front(); q.pop();
    ord.push(x);
    trav(it, eds[x]) {
      if (--outdeg[it] == 0) {
        q.push(it);
      }
    }
  }

  trav(it, ord) {
  }
}
