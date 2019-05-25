#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define trav(it, v) for(auto &it : (v))
#define all(v) (v).begin(), (v).end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef ll T;

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
	P perp() const { return P(-y, x); } // rotates +90 degrees
};

bool colinear(Point a, Point b, Point c) {
	return a.cross(b, c) == 0;
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		cerr << "Wrong number of arguments to gen_nocolinear" << endl;
		return 1;
	}
	int N = atoi(argv[1]);
	int maxx = atoi(argv[2]);
	int seed = atoi(argv[3]);
	srand(seed);
	vector<Point> points;
	while (sz(points) < N) {
		Point p;
		p.x = (rand()%(2*maxx+1))-maxx;
		p.y = (rand()%(2*maxx+1))-maxx;
		for (int i = 0; i < sz(points); i++) {
			if (points[i] == p) goto fail;
		}
		for (int i = 0; i < sz(points); i++) {
			for (int j = i+1; j < sz(points); j++) {
				if (colinear(points[i], points[j], p)) goto fail;
			}
		}
		points.push_back(p);
fail:;
	}
	cout << sz(points) << endl;
	for (auto point : points) {
		cout << point.x << " " << point.y << endl;
	}
}
