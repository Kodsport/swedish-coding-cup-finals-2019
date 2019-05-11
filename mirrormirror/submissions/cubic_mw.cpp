#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
#define rrep(i, a, b) for(int i = (a) - 1; i >= int(b); --i)
#define trav(it, v) for(auto &it : (v))
#define all(v) (v).begin(), (v).end()
#define what_is(x) cerr << #x << " is " << x << endl;
#define sz(x) (int)(x).size()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

struct Rat {
    ll x, y;

    Rat(ll _x, ll _y) {
        x = _x;
        y = _y;
        if (y < 0) {
            x = -x;
            y = -y;
        }
    }

    Rat operator+(const Rat& other) const {
        return Rat(x*other.y+y*other.x, y*other.y);
    }

    Rat operator-(const Rat& other) const {
        return Rat(x*other.y-y*other.x, y*other.y);
    }
    
    Rat operator*(const Rat& other) const {
        return Rat(x*other.x, y*other.y);
    }

    bool operator<(const Rat& other) const {
        return x * other.y < y * other.x;
    }

    bool operator==(const Rat& other) const {
        return x * other.y == y * other.x;
    }

    bool operator!=(const Rat& other) const {
        return x * other.y != y * other.x;
    }

    void reduce() {
        ll g = __gcd(x, y);
        x /= g;
        y /= g;
    }
};

struct Point {
    int x, y;
};

struct Line {
    Rat k, m;

    Line(Rat _k, Rat _m) : k(_k), m(_m) {}

    bool operator<(const Line& other) const {
        if (k != other.k)
            return k < other.k;
        return m < other.m;
    }
};

Line getLine(const Point& p1, const Point& p2) {
    ll dx = p2.x-p1.x;
    if (dx == 0) {
        return Line(Rat(1, 0), Rat(p1.x, 1));
    }
    ll dy = p2.y-p1.y;
    Rat k(dy, dx);
    Rat m = Rat(p1.y, 1) - k * Rat(p1.x, 1);
    return Line(k, m);
}

Line getOrthogonalLine(const Point& p1, const Point& p2) {
    int dy = p2.y-p1.y;
    if (dy == 0) {
        return Line(Rat(1, 0), Rat(p1.x+p2.x, 2));
    }
    int dx = p2.x-p1.x;
    Rat k(-dx, dy);
    Rat m = Rat(p1.y+p2.y, 2) - k * Rat(p1.x+p2.x, 2);
    return Line(k, m);
}

int main(){
	ios::sync_with_stdio(0);
    int N;
    cin >> N;
    vector<Point> points;
    rep(i,0,N) {
        Point p;
        cin >> p.x >> p.y;
        points.push_back(p);
    }
    map<Line, int> lines;
    rep(i,0,N) {
        Point p1 = points[i];
        rep(j,i+1,N) {
            Point p2 = points[j];
            Line l1 = getLine(p1, p2);
            lines[l1] += 0;
            Line l2 = getOrthogonalLine(p1, p2);
            lines[l2] += 2;
        }
    }
    ll ans = 1;
    for (auto it : lines) {
        Line line = it.first;
        ll res = it.second;
        rep(i,0,N) {
            Point p = points[i];
            if (line.k.y == 0) {
                if (line.m.x == line.m.y * p.x)
                    ++res;
            }
            else {
                if (line.k * Rat(p.x, 1) + line.m == Rat(p.y, 1))
                    ++res;
            }
        }
        ans = max(ans, res);
    }
    cout << ans << endl;
}
