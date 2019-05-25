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

struct Command {
    string type;
    string arg;
};

struct Function {
    vector<Command> commands;

    void rec(set<string>& acquired);
};

map<string, Function> functions;

int exec;

void Function::rec(set<string>& acquired) {
    for (Command& c : commands) {
        exec++;
        if (c.type == "acquire") {
            if (acquired.count(c.arg)) {
                cout << "deadlock" << endl;
                exit(0);
            }
            acquired.insert(c.arg);
        }
        else if (c.type == "release") {
            if (acquired.count(c.arg) == 0) {
                cout << "error" << endl;
                exit(0);
            }
            acquired.erase(c.arg);
        }
        else if (c.type == "access") {
            if (acquired.count(c.arg) == 0) {
                cout << "corruption" << endl;
                exit(0);
            }
        }
        else if (c.type == "call") {
            functions[c.arg].rec(acquired);
        }
        else {
            assert(0);
        }
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
        rep(j,0,M) {
            Command c;
            cin >> c.type >> c.arg;
            f.commands.push_back(c);
        }
        functions[name] = f;
    }
    set<string> acquired;
    functions["main"].rec(acquired);
    cout << "a-ok" << endl;
    cerr << exec << " instructions executed" << endl;
}
