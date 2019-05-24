from util import *
import math

# returns true if p is left of vector from a to b
def left(a, b, p):
    d = (b[0] - a[0], b[1] - a[1])
    e = (p[0] - a[0], p[1] - a[1])
    return d[0]*e[1] - d[1]*e[0] > 0

def right(a, b, p):
    return not left(a, b, p)

# generate convex hull
def graham_scan(pointList):
    bottomPoint = (30001, 0)
    for p in pointList:
        bottomPoint = min(bottomPoint, (p[1], p[0]))
    bottomPoint = (bottomPoint[1], bottomPoint[0])

    anglePointList = []
    for point in pointList:
        if point == bottomPoint:
            continue
        dx = point[0] - bottomPoint[0]
        dy = point[1] - bottomPoint[1]
        dist = math.sqrt(dx*dx + dy*dy)
        angle = math.acos(dx/dist)
        anglePointList.append([angle, point])

    hullStack = []
    anglePointList.sort()
    for apoint in anglePointList:
        point = apoint[1]
        while len(hullStack) > 1 and right(hullStack[-2], hullStack[-1], point):
            hullStack.pop()
        hullStack.append(point)

    return hullStack

n    = int(cmdlinearg('n'))
maxx = int(cmdlinearg('maxx'))
fact = float(cmdlinearg('fact'))
wobble = int(cmdlinearg('wobble'))
odd = int(cmdlinearg('odd', 0))
rand = int(cmdlinearg('rand', 1))

genN = int(fact*n)
points = set()

centerX = float(random.randint(-maxx//300, maxx//300))
centerY = float(random.randint(-maxx//300, maxx//300))
radius = float(random.randint(maxx - maxx//300 - 1000, maxx - maxx//300 - 1))

if odd:
    oddPoint = (round(centerX), round(centerY + radius))
    points.add(oddPoint)

for i in range(genN):
    angle = random.uniform(0, 2*math.pi)
    x = round((radius - random.uniform(0, wobble)) * math.cos(angle) + centerX)
    y = round((radius - random.uniform(0, wobble)) * math.sin(angle) + centerY)
    points.add((x,y))
    if odd:
        points.add((2*round(centerX)-x,y))

hullPoints = graham_scan(sorted(list(points)))

if rand:
    random.shuffle(hullPoints)
if odd and oddPoint in hullPoints:
    ind = hullPoints.index(oddPoint)
    hullPoints[0], hullPoints[ind] = hullPoints[ind], hullPoints[0]

while len(hullPoints) > n:
    hullPoints.pop()

random.shuffle(hullPoints)

print(len(hullPoints))
for (x, y) in hullPoints:
    print(x, y)

