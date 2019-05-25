#include "validator.h"
using namespace std;

void run() {
	long long xz = Arg("maxW");
	long long x = Int(25, xz);
	Space();
	long long z = Int(25, xz);
	Space();
	Int(1, Arg("maxK"));
	Endl();
	assert(x % 25 == 0);
	assert(z % 25 == 0);
}
