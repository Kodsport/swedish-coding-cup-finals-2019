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
    bottomPoint = (30000, 0)
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

genN = 400*n
points = set()

centerX = float(random.randint(-maxx//300, maxx//300))
centerY = float(random.randint(-maxx//300, maxx//300))
radius = float(random.randint(maxx - 1000, maxx - 1))

for i in range(genN):
    angle = random.uniform(0, 2*math.pi)
    x = int(radius*math.cos(angle) + centerX)
    y = int(radius*math.sin(angle) + centerY)
    points.add((x,y))

hullPoints = graham_scan(list(points))

while len(hullPoints) > n:
    hullPoints.pop()

print(len(hullPoints))
for (x, y) in hullPoints:
    print(x, y)

