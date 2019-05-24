from util import *
import random

MAXK = 1000000000
a = int(cmdlinearg('a'))
m = int(cmdlinearg('m'))
a = min(a, MAXK // m)

A = [random.randint(1, a) for _ in range(m)]
s = sum(A)
k = random.randint(s // 2 + 1, s)

print(m, k)
print(*A)
