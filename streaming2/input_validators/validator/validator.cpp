#include "validator.h"
using namespace std;

void run() {
	int n = Int(1, Arg("n"));
	Space();
	int k = Int(1, Arg("k"));
	Endl();
	assert(k <= n);
	for (int i = 0; i < n; i++) {
		char c = Char();
		assert(c == '1' || c == '2' || c == 'B');
	}
	Endl();
}
