from util import *
import random

suma = int(cmdlinearg('suma'))
m = int(cmdlinearg('groups'))

ps = [0] + sorted(random.sample(range(1, suma), m - 1)) + [suma]
A = [e - b for b, e in zip(ps[:-1], ps[1:])]
k = random.randint(100, 1000)

print(m, k)
print(*A)
