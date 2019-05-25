from util import *
import random
import math

maxW = int(cmdlinearg('maxW'))
maxK = int(cmdlinearg('maxK'))
type = cmdlinearg('ival')

def rdown(x):
    return x - (x % 25)

def dec(x):
    return rdown(x * 9 // 10)

X = rdown(random.randint(25, maxW))
K = random.randint(1, min(maxK, (maxW - X) // 25))

if type == "begin":
    Z = X
    failK = random.randint(0, min(K, int(math.log(X) / math.log(1.1))))
    for i in range(failK):
        Z = dec(Z)
    Z += 25 * (K - failK)

elif type == "beginzero":
    Z = X
    failK = random.randint(0, min(K, int(math.log(X) / math.log(1.1))))
    Z = 25 * (K - failK)

elif type == "mid":
    failK = random.randint(0, min(K, int(math.log(X) / math.log(1.1))))

    hiZ = X
    for i in range(failK):
        hiZ = dec(hiZ)
    hiZ += 25 * (K - failK)

    loZ = X
    for i in range(failK):
        loZ = dec(loZ)
    loZ += 25 * (K - failK)

    Z = rdown((loZ + hiZ) // 2)

elif type == "end":
    Z = X
    failK = random.randint(0, min(K, int(math.log(X) / math.log(1.1))))
    for i in range(failK):
        Z = dec(Z)
    Z += 25 * (K - failK)

elif type == "underbegin":
    Z = X
    failK = random.randint(0, min(K, int(math.log(X) / math.log(1.1))))
    for i in range(failK):
        Z = dec(Z)
    Z += 25 * (K - failK - 1)

elif type == "overend":
    Z = X
    failK = random.randint(0, min(K, int(math.log(X) / math.log(1.1))))
    for i in range(failK):
        Z = dec(Z)
    Z += 25 * (K - failK + 1)

print(X, max(25, min(maxW, Z)), max(1, min(maxK, K)))
