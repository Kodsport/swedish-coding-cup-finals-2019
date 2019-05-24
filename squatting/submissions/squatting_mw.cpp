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

struct Node {
    map<string, Node*> lString;
    map<string, Node*> rString;
    string s;
    int numStrings;

    Node() {
        numStrings = 0;
    }

    void addString(string t) {
        if (t != s) {
            ++numStrings;
            if (s != "") {
                addString(s);
                s = "";
            }
        }
        if (sz(t) == 1)
            return;
        int mid = sz(t)/2;
        string t1 = t.substr(0, mid);
        string t2 = t.substr(mid);
        auto it = lString.find(t1);
        if (it == lString.end()) {
            Node* node = new Node();
            node->s = t2;
            node->numStrings = 1;
            lString[t1] = node;
        }
        else {
            lString[t1]->addString(t2);
        }
        it = rString.find(t2);
        if (it == rString.end()) {
            Node* node = new Node();
            node->s = t1;
            node->numStrings = 1;
            rString[t2] = node;
        }
        else {
            rString[t2]->addString(t1);
        }
    }

    int get(string t) {
        if (numStrings == 1)
            return 0;
        if (sz(t) == 1)
            return numStrings - 1;
        int ret = 0;
        int mid = sz(t)/2;
        string t1 = t.substr(0, mid);
        string t2 = t.substr(mid);
        auto it = lString.find(t1);
        ret += lString[t1]->get(t2);
        it = rString.find(t2);
        ret += rString[t2]->get(t1);
        return ret;
    }

    ~Node() {
        for (auto it : lString) {
            delete it.second;
        }
        for (auto it : rString) {
            delete it.second;
        }
    }
};

map<string, int> ans;

void solve(const vector<string>& domains) {
    Node root;
    for (string domain : domains) {
        root.addString(domain);        
    }
    for (string domain : domains) {
        ans[domain] = root.get(domain);        
    }
}

int main(){
	ios::sync_with_stdio(0);
    int N;
    cin >> N;
    map<int, vector<string>> domainsByLength;
    vector<string> domains;
    rep(i,0,N) {
        string domain;
        cin >> domain;
        domains.push_back(domain);
        domainsByLength[sz(domain)].push_back(domain);
    }
    for (auto it : domainsByLength) {
        solve(it.second);
    }
    rep(i,0,N) {
        cout << ans[domains[i]] << endl;
    }
}
