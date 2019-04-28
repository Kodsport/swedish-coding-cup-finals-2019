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

struct line{
	ll yc, xc, cc;
	line(ll yc, ll xc, ll cc) : yc(yc), xc(xc), cc(cc) {};
};

bool operator<(const line& a, const line& b) { return a.yc * b.xc < b.yc * a.xc; }
bool operator==(const line& a, const line& b) { return a.yc == b.yc && a.xc == b.xc && a.cc == b.cc; }

ll gcd(ll a, ll b){
	if(a == 0) return b;
	return gcd(b % a, a);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	ll x, y;
	vector <pair <ll, ll>> p;
	rep(i, 0, n){
		cin >> x >> y;
		p.push_back({x, y});
	}

	if(n == 1){
		cout << 1 << endl;
		return 0;
	}

	vector <line> thru, pbis;
	rep(i, 0, n) rep(j, i + 1, n){

		// Linjen genom pi och pj
		ll yc = p[j].X - p[i].X;
		ll xc = p[i].Y - p[j].Y;
		ll cc = p[i].X * p[j].Y - p[j].X * p[i].Y;
		ll div = gcd(abs(yc), gcd(abs(xc), abs(cc)));
		if(yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0)))) div *= -1;
		yc /= div; xc /= div; cc /= div;
		thru.push_back(line(yc, xc, cc));

		// Mittpunktsnormalen till pi och pj
		yc = 2 * (p[j].Y - p[i].Y);
		xc = 2 * (p[j].X - p[i].X);
		cc = p[i].Y * p[i].Y - p[j].Y * p[j].Y + p[i].X * p[i].X - p[j].X * p[j].X;
		div = gcd(abs(yc), gcd(abs(xc), abs(cc)));
		if(yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0)))) div *= -1;
		yc /= div; xc /= div; cc /= div;
		pbis.push_back(line(yc, xc, cc));
	}

	vector <line> swaps;
	rep(i, 0, sz(thru)){
		while(i < sz(thru) - 1){
			if(thru[i] == thru[i + 1]) i++;
			else break;
		}
		swaps.push_back(thru[i]);
	}

	sort(all(swaps));
	sort(all(pbis));

	int best = 0;
	int swi = 0, pbi = 0;
	ll ycsw = swaps[swi].yc, xcsw = swaps[swi].xc;
	ll ycpb = pbis[pbi].yc, xcpb = pbis[pbi].xc;

	vi q(n);
	iota(all(q), 0);
	sort(all(q), [p](int i, int j){
		if(p[i].X == p[j].X) return p[i].Y > p[j].Y;
		return p[i].X < p[j].X;
	});

	while(true){
		if(ycsw * xcpb < ycpb * xcsw){

			// Utför nästa swap
			int a = 0, b = n, mid;
			ll cncc = -swaps[swi].cc;
			while(a + 1 != b){
				mid = (a + b) / 2;
				ll midncc = ycsw * p[q[mid]].Y + xcsw * p[q[mid]].X;
				if(cncc < midncc) b = mid;
				else a = mid;
			}
			a = 0;
			for(int i = b - 1; i >= 0; i--){
				if(ycsw * p[q[i]].Y + xcsw * p[q[i]].X != cncc){
					a = i + 1;
					break;
				}
			}
			rep(i, 0, (b - a) / 2) swap(q[a + i], q[b - i - 1]);
			swi++;
			if(swi == sz(swaps)) ycsw = 0, xcsw = -1;
			else ycsw = swaps[swi].yc, xcsw = swaps[swi].xc;
		}
		else{

			// Utför nästa beräkning
			int countpbis = 1;
			while(pbi < sz(pbis) - 1){
				if(pbis[pbi] == pbis[pbi + 1]) pbi++, countpbis++;
				else break;
			}
			int lbl, fal;
			int a = 0, b = n, mid;
			ll cncc = -pbis[pbi].cc;
			while(a + 1 != b){
				mid = (a + b) / 2;
				ll midncc = ycpb * p[q[mid]].Y + xcpb * p[q[mid]].X;
				if(midncc < cncc) a = mid;
				else b = mid;
			}
			lbl = a;
			a = 0, b = n;
			while(a + 1 != b){
				mid = (a + b) / 2;
				ll midncc = ycpb * p[q[mid]].Y + xcpb * p[q[mid]].X;
				if(cncc < midncc) b = mid;
				else a = mid;
			}
			fal = b;
			best = max(best, 2 * countpbis + fal - lbl - 1);
			pbi++;
			if(pbi == sz(pbis)) break;
			else ycpb = pbis[pbi].yc, xcpb = pbis[pbi].xc;
		}
	}

	cout << best << endl;
}