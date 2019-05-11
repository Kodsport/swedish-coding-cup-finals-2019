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

    Rat operator-(const Rat& other) const {
        return Rat(x*other.y-y*other.x, y*other.y);
    }
    
    Rat operator*(const Rat& other) const {
        return Rat(x*other.x, y*other.y);
    }

    bool operator<(const Rat& other) const {
        return x * other.y < y * other.x;
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

    int getDis2(const Point& other) const {
        int dx = x-other.x;
        int dy = y-other.y;
        return dx*dx + dy*dy;
    }
};

struct Line {
    Rat k, m;

    Line(Rat _k, Rat _m) : k(_k), m(_m) {
        k.reduce();
        m.reduce();
    }

    bool operator<(const Line& other) const {
        if (k != other.k)
            return k < other.k;
        return m < other.m;
    }

    ll getHash() {
        return 1000000000LL * k.x + 100000 * k.y + 1000 * m.x + m.y;
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
    unordered_map<ll, map<Line, int>> lineToInd;
    int lineCount = 0;
    vector<vector<int>> lineInd(N, vector<int>(N));
    vector<int> symmetricPoints;
    vector<set<int>> pointsOnLine;
    rep(i,0,N) {
        Point p1 = points[i];
        rep(j,0,N) {
            if (i == j)
                lineInd[i][j] = -1;
            else if (i > j) {
                lineInd[i][j] = lineInd[j][i];
            }
            else {
                Point p2 = points[j];
                Line l = getOrthogonalLine(p1, p2);
                ll h = l.getHash();
                if (!lineToInd[h].count(l)) {
                    lineToInd[h][l] = lineCount++;
                    symmetricPoints.emplace_back();
                    pointsOnLine.emplace_back();
                }
                lineInd[i][j] = lineToInd[h][l];
                symmetricPoints[lineInd[i][j]] += 2;
            }
        }
    }
    ll ops = 0;
    rep(i,0,N) {
        Point p1 = points[i];
        map<int, vector<int>> pointsAtDis;
        rep(j,0,N) {
            pointsAtDis[p1.getDis2(points[j])].push_back(j);
        }
        for (auto it : pointsAtDis) {
            const vector<int>& v = it.second;
            rep(j,0,sz(v))
                rep(k,j+1,sz(v)) {
                    ops++;
                    pointsOnLine[lineInd[v[j]][v[k]]].insert(i);
                }
        }
    }
    int ans = 1;
    rep(i,0,sz(pointsOnLine)) {
        ans = max(ans, symmetricPoints[i] + sz(pointsOnLine[i]));
    }
    unordered_map<ll, map<Line, unordered_set<int>>> lines;
    rep(i,0,N) {
        Point p1 = points[i];
        rep(j,i+1,N) {
            Point p2 = points[j];
            Line l = getLine(p1, p2);
            auto& it = lines[l.getHash()][l];
            it.insert(i);
            it.insert(j);
            ans = max(ans, sz(it));
        }
    }
    cout << ans << endl;
    exit(0);
}
