from random import randint
from util import *

S    = int(cmdlinearg('S'))
minLength    = int(cmdlinearg('minLength'))
maxLength    = int(cmdlinearg('maxLength'))

domains = set()
attemptsLeft = 1e7//minLength
while S > 0 and attemptsLeft > 0:
    attemptsLeft -= 1
    length = randint(minLength, maxLength)
    if length > S:
        length = S
    domain = ""
    for i in range(length):
        domain += (chr(ord('a')+randint(0, 25)))
    if not domain in domains:
        domains.add(domain)
        S -= length

print(len(domains))
for domain in domains:
    print(domain)
