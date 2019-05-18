from random import randint
from util import *

S    = int(cmdlinearg('S'))
minLength    = int(cmdlinearg('minLength'))
maxLength    = int(cmdlinearg('maxLength'))

domains = set()
while S > 0:
    length = randint(minLength, maxLength)
    if length > S:
        length = S
    domain = ""
    for i in range(length):
        domain += (chr(ord('a')+randint(0, 25)))
    domains.add(domain)
    S -= length

print(len(domains))
for domain in domains:
    print(domain)
