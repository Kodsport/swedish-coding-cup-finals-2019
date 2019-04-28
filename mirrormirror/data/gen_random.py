from util import *

n    = int(cmdlinearg('n'))
maxx = int(cmdlinearg('maxx'))

points = set()
i = 0
while len(points) < n and i < n * 10:
    i += 1

    x = random.randint(-maxx, maxx)
    y = random.randint(-maxx, maxx)

    points.add((x, y))

print(len(points))

for (x, y) in points:
    print(x, y)
