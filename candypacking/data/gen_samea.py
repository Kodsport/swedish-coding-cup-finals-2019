from util import *
import random

a = int(cmdlinearg('a'))
m = int(cmdlinearg('m'))
k = int(cmdlinearg('k'))

print(m, k)
print(*[a for _ in range(m)])
