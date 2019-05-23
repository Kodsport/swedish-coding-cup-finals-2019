#include "validator.h"
using namespace std;

void run() {
	long long maxsum = Arg("s");
	int n = Int(1, Arg("n"));
	Endl();
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		for (;;) {
			char c = Char();
			if (c == '\n') break;
			assert('a' <= c && c <= 'z');
			sum++;
		}
	}
	assert(sum <= maxsum);
}
