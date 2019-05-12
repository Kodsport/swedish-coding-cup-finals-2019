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

    ll getDis2(const Point& other) const {
        ll dx = x-other.x;
        ll dy = y-other.y;
        return dx*dx + dy*dy;
    }

    bool operator<(const Point& other) const {
        return make_pair(x, y) < make_pair(other.x, other.y);
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

set<Point> getBadPoints(vector<Point> points) {
    set<Point> badPoints;
    map<Line, int> lineToInd;
    int lineCount = 0;
    int N = sz(points);
    vector<vector<int>> lineInd(N, vector<int>(N));
    vector<int> symmetricPoints;
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
                if (!lineToInd.count(l)) {
                    lineToInd[l] = lineCount++;
                    symmetricPoints.emplace_back();
                }
                lineInd[i][j] = lineToInd[l];
                symmetricPoints[lineInd[i][j]] += 2;
                if (symmetricPoints[lineInd[i][j]] >= 4) {
                    badPoints.insert(p1);
                    badPoints.insert(p2);
                }
            }
        }
    }
    lineToInd.clear();
    symmetricPoints.clear();
    bool hasAdded3 = false;
    rep(i,0,N) {
        Point p1 = points[i];
        map<ll, vector<int>> pointsAtDis;
        rep(j,0,N) {
            pointsAtDis[p1.getDis2(points[j])].push_back(j);
        }
        for (auto it : pointsAtDis) {
            const vector<int>& v = it.second;
            rep(j,0,sz(v))
                rep(k,j+1,sz(v)) {
                    if (hasAdded3) {
                        badPoints.insert(p1);
                    }
                    else {
                        hasAdded3 = true;
                    }
                }
        }
    }
    lineInd.clear();
    map<Line, unordered_set<int>> lines;
    rep(i,0,N) {
        Point p1 = points[i];
        rep(j,i+1,N) {
            Point p2 = points[j];
            Line l = getLine(p1, p2);
            auto& it = lines[l];
            it.insert(i);
            it.insert(j);
            if (sz(it) > 2) {
                badPoints.insert(p1);
                badPoints.insert(p2);
            }
        }
    }
    return badPoints;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Wrong number of arguments to gen_answer_is_2" << endl;
        return 1;
    }
    int N = atoi(argv[1]);
    int maxx = atoi(argv[2]);
    int seed = atoi(argv[3]);
    srand(seed);
    set<Point> points;
    while (sz(points) < N) {
        Point p;
        p.x = (rand()%(2*maxx+1))-maxx;
        p.y = (rand()%(2*maxx+1))-maxx;
        points.insert(p);
        if (sz(points) == N) {
            vector<Point> ps;
            for (auto q : points)
                ps.push_back(q);
            set<Point> badPoints = getBadPoints(ps);
            for (auto badPoint : badPoints) {
                points.erase(badPoint);
            }
        }
    }
    cout << sz(points) << endl;
    for (auto point : points) {
        cout << point.x << " " << point.y << endl;
    }
}
