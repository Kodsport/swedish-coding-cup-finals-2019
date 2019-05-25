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
string s;
map<pair<int, pair<int, int>>, int> cache;

int rec(int day, int d1, int d2) {
    if (day == N)
        return 0;
    if (d1 < 0)
        d1 = 0;
    if (d2 < 0)
        d2 = 0;
    auto key = make_pair(day, make_pair(d1, d2));
    if (cache.count(key))
        return cache[key];
    int ret = 1e9;
    bool ok = false;
    if (d1 && (s[day] == '1' || s[day] == 'B'))
        ok = true;
    if (d2 && (s[day] == '2' || s[day] == 'B'))
        ok = true;
    if (!ok) {
        if (!d1 && (s[day] == '1' || s[day] == 'B')) {
            ret = min(ret, rec(day, K, d2)+1);
        }
        if (!d2 && (s[day] == '2' || s[day] == 'B')) {
            ret = min(ret, rec(day, d1, K)+1);
        }
        cache[key] = ret;
        return ret;
    }
    ret = rec(day+1, d1-1, d2-1);
    cache[key] = ret;
    return ret;
}

int main(){
	ios::sync_with_stdio(0);
    cin >> N >> K >> s;
    int ans = rec(0, 0, 0);
    cout << ans << endl;
	_Exit(0);
}
