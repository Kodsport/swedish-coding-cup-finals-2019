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

int main(){
	ios::sync_with_stdio(0);
    ll M, K;
    cin >> M >> K;
    vector<ll> a(M);
    rep(i,0,M) {
        cin >> a[i];
    }
    ll maxA = *max_element(all(a));
    ll sumA = accumulate(all(a), 0LL);
    ll boxes = sumA/K;
    ll modified = 0;
    if (boxes == 1) {
        ll sum = 0;
        rep(i,0,M) {
            sum += min(K-1, max(1LL, a[i]-1));
        }
        vector<ll> costs;
        rep(i,0,M) {
            if (a[i] > 1) {
                if (a[i] > K) {
                    costs.push_back(1);
                }
                else {
                    costs.push_back(a[i]-1);
                }
            }
        }
        sort(all(costs));
        rep(i,0,sz(costs)) {
            if (sum < K) {
                modified += costs[i];
                ++sum;
            }
        }
    }
    else if (sumA - maxA < boxes) {
        modified = boxes - (sumA - maxA);
    }
    cout << boxes << " " << modified << endl;
}
