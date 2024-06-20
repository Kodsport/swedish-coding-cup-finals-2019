#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
typedef long long ll;

int main() {
	ll start, goal, days;
	cin >> start >> goal >> days;
	start /= 25;
	goal /= 25;
	rep(fails,0,days+1) {
		ll smallest = start + (days - fails);
		ll largest = start;
		rep(i,0,fails) {
			smallest = smallest * 9 / 10;
			largest = largest * 9 / 10;
		}
		largest += (days - fails);
		if (smallest <= goal && goal <= largest) {
			cout << "biceps" << endl;
			return 0;
		}
		if (smallest == 0) {
			break;
		}
	}
	cout << "liar" << endl;
}
