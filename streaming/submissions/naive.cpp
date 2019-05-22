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
    
int N, K;
string S;

struct Key {
    int day, d1, d2, e1, e2;

    Key(int _day, int _d1, int _d2, int _e1, int _e2) : day(_day), d1(_d1), d2(_d2), e1(_e1), e2(_e2) {}

    bool operator<(const Key& other) const {
        if (day != other.day) return day < other.day;
        if (d1 != other.d1) return d1 < other.d1;
        if (d2 != other.d2) return d2 < other.d2;
        if (e1 != other.e1) return e1 < other.e1;
        if (e2 != other.e2) return e2 < other.e2;
        return false;
    }
};

map<Key, int> cache;

int rec(int day, int d1, int d2, int e1, int e2) {
    if (day == N)
        return 0;
    if (d1 < 0)
        d1 = 0;
    if (d2 < 0)
        d2 = 0;
    Key key(day, d1, d2, e1, e2);
    if (cache.count(key))
        return cache[key];
    int ret = 1e9;
    if (S[day] == '1' || S[day] == 'B')
        ++e1;
    if (S[day] == '2' || S[day] == 'B')
        ++e2;
    if (d1 && e1) {
        ret = min(ret, rec(day+1, d1-1, d2-1, e1-1, e2));
    }
    if (d2 && e2) {
        ret = min(ret, rec(day+1, d1-1, d2-1, e1, e2-1));
    }
    ret = min(ret, 1+rec(day+1, K-1, d2-1, e1-1, e2));
    ret = min(ret, 1+rec(day+1, d1-1, K-1, e1, e2-1));
    cache[key] = ret;
    return ret;
}

int main(){
	ios::sync_with_stdio(0);
    cin >> N >> K >> S;
    cout << rec(0, 0, 0, 0, 0) << endl;
}
