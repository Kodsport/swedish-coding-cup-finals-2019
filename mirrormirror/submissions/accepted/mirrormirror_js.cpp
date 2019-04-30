#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T dist2() const { return x*x + y*y; }
	P perp() const { return P(-y, x); } // rotates +90 degrees
};

typedef Point<int> P;
typedef tuple<ll, ll, ll> Line;

Line normalLine(P f, P s, P t) {
  ll a = s.x - f.x;
  ll b = s.y - f.y;
  ll c = ll(t.x) * (s.x - f.x) + ll(t.y) * (s.y - f.y);
  ll g = __gcd(a, __gcd(b, c));
  a /= g;
  b /= g;
  c /= g;
  if (a < 0) a = -a, b = -b, c = -c;
  if (a == 0 && b < 0) b = -b, c = -c;
  return Line {a, b, c};
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

  int N;
  cin >> N;
  vector<vi> normal(N, vi(N));
  vector<P> C(N);
  trav(it, C) cin >> it.x >> it.y;
  trav(it, C) it.x *= 2, it.y *= 2;

  rep(i,0,N) {
    map<ll, vector<int>> pts;
    rep(j,0,N) {
      if (i == j) continue;
      pts[(C[i]-C[j]).dist2()].push_back(j);
    }
    trav(it, pts) {
      trav(p1, it.second) {
        trav(p2, it.second) {
          normal[p1][p2]++;
        }
      }
    }
  }

  vector<pair<Line, int>> lines;
  vector<Line> lines2;

  rep(i,0,N) rep(j,0,i) {
    P f = C[i], s = C[j];
    Line mid = normalLine(f, s, (f + s) / 2);
    Line through = normalLine(f, f + (s - f).perp(), f);
    lines.emplace_back(mid, normal[i][j]);
    lines2.push_back(through);
  }
  sort(all(lines));
  sort(all(lines2));

  int ans = 1, cur = 0, norm = -1;
  Line prev(-1e9, -1e9, -1e9);
  trav(it, lines) {
    if (prev == it.first) {
      cur++;
    } else {
      ans = max(ans, 2 * cur + norm);
      cur = 1;
    }
    norm = it.second;
    prev = it.first;
  }
  ans = max(ans, 2 * cur + norm);

  map<int, int> pairs;
  rep(i,2,N+1) pairs[i * (i - 1) / 2] = i;
  cur = 0;
  prev = Line(-1e9, -1e9, -1e9);
  trav(it, lines2) {
    if (prev == it) cur++;
    else ans = max(ans, pairs[cur]), cur = 1;
    prev = it;
  }
  ans = max(ans, pairs[cur]);
  cout << ans << endl;
  _Exit(0);
}
