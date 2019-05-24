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

// Euklides algoritm
ll gcd(ll a, ll b){
    if(a == 0) return b;
    return gcd(b % a, a);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	// Läs in punkter
	ll x, y;
	vector <pair <ll, ll>> p;
	rep(i, 0, n){
		cin >> x >> y;
		p.push_back({x, y});
	}

	// Fallet en ensam punkt
	if(n == 1){
		cout << 1 << endl;
		return 0;
	}

	// n >= 2 nu
	// Vektorer innehållande koefficienter för linjer
	// thru innehåller linjer genom pi och pj
	// pbis innehåller mittpunktsnormaler till pi och pj (Perpendicular BISectors)
	vector <tuple <ll, ll, ll>> thru, pbis;
	//      ^ Koefficienter

	// Gå igenom alla punktpar (pi, pj), i < j
	rep(i, 0, n) rep(j, i + 1, n){

		// Linjen som går genom (xi, yi) och (xj, yj) har ekvationen
		//     (xj - xi)(y - yi) = (yj - yi)(x - xi)
		//     (xj - xi)y + (yi - yj)x + (xi * yj - xj * yi) = 0
		//     ---yc----    ---xc----    --------cc---------
		// Koefficienterna delat med deras sgd identifierar linjen unikt
		ll yc = p[j].X - p[i].X;
		ll xc = p[i].Y - p[j].Y;
		ll cc = p[i].X * p[j].Y - p[j].X * p[i].Y;

		// sgd(a, b, c) == sgd(a, sgd(b, c))
		// Koefficienter kan vara negativa
		// Standardisera så att första icke-noll koefficient är positiv
		ll div = gcd(abs(yc), gcd(abs(xc), abs(cc)));
		if(yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0)))) div *= -1;

		// div == 0 omm yc == xc == cc == 0
		// Detta inträffar bara om pi == pj, vilket är garanterat att inte hända
		// Alltså kan vi dividera
		yc /= div;
		xc /= div;
		cc /= div;

		// Lägg in linjen i linjevektorn
		thru.push_back({yc, xc, cc});

		// Nu till mittpunktsnormalen
		// Lutningen är -(xj - xi)/(yj - yi)
		// Den går genom ((xi + xj) / 2, (yi + yj) / 2)
		//     (yj - yi)(y - (yi + yj) / 2) = -(xj - xi)(x - (xi + xj) / 2)
		//     (yj - yi)(2y - yi - yj) + (xj - xi)(2x - xi - xj) = 0
		//     2(yj - yi)y + 2(xj - xi)x + yi^2 - yj^2 + xi^2 - xj^2 = 0
		// Uppprepa processen med koefficienterna
		yc = 2 * (p[j].Y - p[i].Y);
		xc = 2 * (p[j].X - p[i].X);
		cc = p[i].Y * p[i].Y - p[j].Y * p[j].Y + p[i].X * p[i].X - p[j].X * p[j].X;
		
		div = gcd(abs(yc), gcd(abs(xc), abs(cc)));
		if(yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0)))) div *= -1;

		yc /= div;
		xc /= div;
		cc /= div;

		// Lägg in mittpunktsnormalen i mittpunktsnormalvektorn
		pbis.push_back({yc, xc, cc});
	}

	// Sortera så att identiska linjer hamnar bredvid varandra
	sort(all(thru));
	sort(all(pbis));

	int best = 0;

	// Gå igenom varje distinkt linje genom punkter
	// Antag att alla punkter vi söker ligger på den
	rep(i, 0, sz(thru)){

		// Ignorera identiska linjer
		while(i < sz(thru) - 1){
			if(thru[i] == thru[i + 1]) i++;
			else break;
		}

		// Koefficienter för linjen
		ll yc, xc, cc;
		tie(yc, xc, cc) = thru[i];

		// Antal punkter på linjen
		// Det går att räkna ut från antalet identiska linjer, men ...
		//     lösningen är redan kubisk och det här är lättare
		int online = 0;
		rep(j, 0, n){
			// yc*y + xc*x + cc = 0 omm (x, y) på linjen
			if(yc * p[j].Y + xc * p[j].X + cc == 0) online++;
		}

		best = max(best, online);
	}

	// Gå igenom varje distinkt mittpunktsnormal, antag att den är symmetrilinje
	rep(i, 0, sz(pbis)){

		// Hur många mittpunktsnormaler är lika med mittpunktsnormal i?
		int countpbis = 1;
		while(i < sz(pbis) - 1){
			if(pbis[i] == pbis[i + 1]) i++, countpbis++;
			else break;
		}

		// Koefficienter för mittpunktsnormalen
		ll yc, xc, cc;
		tie(yc, xc, cc) = pbis[i];

		// Hur många punkter ligger på mittpunktsnormalen?
		int online = 0;
		rep(j, 0, n){
			// yc*y + xc*x + cc = 0 omm (x, y) på linjen
			if(yc * p[j].Y + xc * p[j].X + cc == 0) online++;
		}

		// Varje punktpar bidrar med 2 punkter
		best = max(best, 2 * countpbis + online);
	}

	cout << best << endl;
}