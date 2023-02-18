#include "validator.h"
#include <numeric>

using namespace std;


void run() {
  int maxM = Arg("maxM");
  int maxA = Arg("maxA");
  int maxK = Arg("maxK");
  long long maxASum = Arg("maxAsum");

	int M = Int(1, maxM);
	Space();
  Int(2, maxK);
  Endl();
  
  vector<int> A = SpacedInts(M, 1, maxA);
  long long sum = accumulate(A.begin(), A.end(), 0LL);
  assert(sum <= maxASum);
}
