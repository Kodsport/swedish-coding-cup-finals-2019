from util import *
import random

maxW = int(cmdlinearg('maxW'))
maxK = int(cmdlinearg('maxK'))

def rdown(x):
    return x - (x % 25)

X = rdown(random.randint(25, maxW))
K = random.randint(1, maxK)
Z = rdown(random.randint(25, min(maxW, X + K * 25)))

print(X, Z, K)
