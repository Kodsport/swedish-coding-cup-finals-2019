from util import *

n = int(cmdlinearg('n'))

print(n)
print(-1, -1)
print(1, 0)
print(0, 1)
print(1, 1)
if n >= 5:
    print(-1, 0)
if n >= 6:
    print(0, -1)
