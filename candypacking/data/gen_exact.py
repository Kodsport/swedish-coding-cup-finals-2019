from util import *
import random

MAXK = 1000000000
a = int(cmdlinearg('a'))
m = int(cmdlinearg('m'))

while True:
    A = [random.randint(1, a) for _ in range(m)]
    s = sum(A)
    for i in range(100, min(s+1, MAXK)):
        if s % i == 0:
            k = i
            break
    else:
        continue
    break

print(m, k)
print(*A)
