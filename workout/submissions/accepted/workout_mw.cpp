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
    
ll X, Z, K;

ll applyReductions(ll X, ll reductions) {
    if (reductions == 0)
        return X;
    if (!X)
        return 0;
    return applyReductions((X*9)/10, reductions-1);
}

ll applyAdds(ll X, ll adds) {
    return X+adds;
}

ll getLowScore(ll X, ll reductions) {
    ll adds = K-reductions;
    return applyReductions(applyAdds(X, adds), reductions);
}

ll getHighScore(ll X, ll reductions) {
    ll adds = K-reductions;
    return applyAdds(applyReductions(X, reductions), adds);
}

int main(){
	ios::sync_with_stdio(0);
    cin >> X >> Z >> K;
    X /= 25;
    Z /= 25;
    ll lo = -1, hi = K+1;
    while (hi - lo > 1) {
        ll mid = (lo+hi)/2;
        if (getLowScore(X, mid) > Z) {
            lo = mid;
        }
        else if (getHighScore(X, mid) < Z) {
            hi = mid;
        }
        else {
            cout << "biceps" << endl;
            return 0;
        }
    }
    cout << "liar" << endl;
}
