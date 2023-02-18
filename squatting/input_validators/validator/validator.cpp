#include "validator.h"
using namespace std;

void run() {
	int maxsum = Arg("s");
	int maxlen = Arg("len", maxsum);
	int n = Int(1, maxsum);
	Endl();
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		int len = 0;
		for (;;) {
			char c = Char();
			if (c == '\n') break;
			assert(('a' <= c && c <= 'z') || ('0' <= c && c <= '9'));
			sum++;
			len++;
		}
		assert(len <= maxlen);
	}
	assert(sum <= maxsum);
}
