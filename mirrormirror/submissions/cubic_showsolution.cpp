// Det här programmet skriver ut punkterna i en maximal lösning, på samma format som i input
// Tanken är att det kan användas för att debugga stora inputfiler.

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(v) v.begin(), v.end()
#define sz(x) (int) (x).size()
typedef pair <int, int> pii;
typedef vector <int> vi;
typedef long long ll;

#define X first
#define Y second

int gcd(int a, int b){
    if(a == 0) return b;
    return gcd(b % a, a);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n, x, y;
	cin >> n;
	vector <pii> p;
	rep(i, 0, n){
		cin >> x >> y;
		p.push_back({x, y});
	}

	if(n == 1){
		cout << 1 << endl;
		return 0;
	}

	vector <pair <tuple <int, int, int>, pair <int, int>>> thru, pbis;
	rep(i, 0, n) rep(j, i + 1, n){
		int yc = p[j].X - p[i].X;
		int xc = p[i].Y - p[j].Y;
		int cc = p[i].X * p[j].Y - p[j].X * p[i].Y;
		int div = gcd(abs(yc), gcd(abs(xc), abs(cc)));
		if(yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0)))) div *= -1;
		yc /= div;
		xc /= div;
		cc /= div;
		thru.push_back({{yc, xc, cc}, {i, j}});

		yc = 2 * (p[j].Y - p[i].Y);
		xc = 2 * (p[j].X - p[i].X);
		cc = p[i].Y * p[i].Y - p[j].Y * p[j].Y + p[i].X * p[i].X - p[j].X * p[j].X;
		div = gcd(abs(yc), gcd(abs(xc), abs(cc)));
		if(yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0)))) div *= -1;
		yc /= div;
		xc /= div;
		cc /= div;
		pbis.push_back({{yc, xc, cc}, {i, j}});
	}

	sort(all(thru));
	sort(all(pbis));

	int best = 0;
	vi bestpoints;
	rep(i, 0, sz(thru)){
		vi currpoints;
		while(i < sz(thru) - 1){
			if(thru[i].first == thru[i + 1].first){
				currpoints.push_back(thru[i].second.first);
				currpoints.push_back(thru[i].second.second);
				i++;
			}
			else break;
		}
		currpoints.push_back(thru[i].second.first);
		currpoints.push_back(thru[i].second.second);

		int yc, xc, cc;
		tie(yc, xc, cc) = thru[i].first;
		int online = 0;
		rep(j, 0, n) if(yc * p[j].Y + xc * p[j].X + cc == 0) online++;
		
		if(online > best){
			best = online;
			bestpoints = currpoints;
		}
	}

	rep(i, 0, sz(pbis)){
		vi currpoints;
		int countpbis = 1;
		while(i < sz(pbis) - 1){
			if(pbis[i].first == pbis[i + 1].first){
				currpoints.push_back(pbis[i].second.first);
				currpoints.push_back(pbis[i].second.second);
				countpbis++;
				i++;
			}
			else break;
		}
		currpoints.push_back(pbis[i].second.first);
		currpoints.push_back(pbis[i].second.second);

		int yc, xc, cc;
		tie(yc, xc, cc) = pbis[i].first;
		int online = 0;
		rep(j, 0, n){
			if(yc * p[j].Y + xc * p[j].X + cc == 0){
				currpoints.push_back(j);
				online++;
			}
		}
		
		if(2 * countpbis + online > best){
			best = 2 * countpbis + online;
			bestpoints = currpoints;
		}
	}

	cout << best << endl;
	rep(i, 0, sz(bestpoints)) cout << p[bestpoints[i]].X << " " << p[bestpoints[i]].Y << endl;
}