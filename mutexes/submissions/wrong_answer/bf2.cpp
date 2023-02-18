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

struct Function {
    vector<Function*> calls;
    int ncommands;

    void rec();
};

map<string, Function> functions;

long long exec;

void Function::rec() {
    exec += ncommands;
    for (Function *c : calls) {
        c->rec();
    }
}

int main(){
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    rep(i,0,N) {
        int M;
        string name;
        cin >> M >> name;
        Function f;
        f.ncommands = 0;
        rep(j,0,M) {
            string type, arg;
            cin >> type >> arg;
            f.ncommands++;
            if (type == "call") {
                f.calls.push_back(&functions[arg]);
            }
        }
        functions[name] = f;
    }
    functions["main"].rec();
    cerr << exec << " instructions executed" << endl;
}
