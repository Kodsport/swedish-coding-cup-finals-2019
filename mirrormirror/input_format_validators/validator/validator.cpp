#include "validator.h"
#include <set>
using namespace std;

void run() {
	int n = Int(1, Arg("n"));
	Endl();
	set<pair<int, int>> s;
	for (int i = 0; i < n; i++) {
		int x = Int(-30'000, 30'000);
		Space();
		int y = Int(-30'000, 30'000);
		Endl();
		s.emplace(x, y);
	}
	assert((int)s.size() == n);
}
