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
    int N;
    cin >> N;
    vector<string> domains(N);
    rep(i,0,N)
        cin >> domains[i];
    rep(i,0,N) {
        ll ans = 0;
        rep(j,0,N) {
            if (sz(domains[i]) != sz(domains[j]))
                continue;
            int diff = 0;
            rep(k,0,sz(domains[i])) {
                if (domains[i][k] != domains[j][k])
                    ++diff;
            }
            if (diff == 1)
                ++ans;
        }
        cout << ans << endl;
    }
}
