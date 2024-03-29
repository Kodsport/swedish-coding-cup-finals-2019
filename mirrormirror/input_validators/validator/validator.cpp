#include "validator.h"
#include <set>
#include <cmath>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		trav(p, pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

void run() {
	int maxCoord = Arg("xMax");
	int n = Int(1, Arg("nMax"));
	bool nocolinear = Arg("nocolinear", 0);
	bool convexhull = Arg("convexhull", 0);
	Endl();
	set<pii> s;
	vector<pii> sv;
	for (int i = 0; i < n; i++) {
		int x = Int(-maxCoord, maxCoord);
		Space();
		int y = Int(-maxCoord, maxCoord);
		Endl();
		s.emplace(x, y);
		sv.push_back({x, y});
	}
	assert((int)s.size() == n);

	if (nocolinear) {
		for (int i = 0; i < n; i++) {
			set<pii> slopes;
			for (int j = i + 1; j < n; j++) {
				int dx = sv[i].first - sv[j].first;
				int dy = sv[i].second - sv[j].second;
				int g = __gcd(dx, dy);
				dx /= g;
				dy /= g;
				if (dx < 0 || (dx == 0 && dy < 0))
					dx *= -1, dy *= -1;
				bool r = slopes.emplace(dx, dy).second;
				assert(r);
			}
		}
	}

	if (convexhull) {
		vector<P> points;
		for (int i = 0; i < n; i++) {
			points.emplace_back(sv[i].first, sv[i].second);
		}
		assert(sz(convexHull(points)) == n);
	}
}
