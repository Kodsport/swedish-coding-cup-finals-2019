from util import *
import random

suma = int(cmdlinearg('suma'))
m = int(cmdlinearg('groups'))
k = random.randint(10, 100)

firstgroup = suma * (k - 1) // k + random.randint(0, suma // k)

ps = [0, firstgroup] + sorted(random.sample(range(firstgroup + 1, suma), m - 2)) + [suma]
A = [e - b for b, e in zip(ps[:-1], ps[1:])]

print(m, k)
print(*A)
