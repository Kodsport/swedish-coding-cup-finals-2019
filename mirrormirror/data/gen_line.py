from util import *

# max number of points
n     = int(cmdlinearg('n'))

# max absolute value of coordinate
maxx  = int(cmdlinearg('maxx'))

# number of lines
lines = int(cmdlinearg('lines'))

# Minimum Points Per Line
mppl = 3

# Each line needs atleast 3 points
assert n >= lines * mppl 

# number of points on each line
def line_size(n, lines):
    while n > 0 and lines > 0:
        lines -= 1

        if lines == 0:
            size = n
        else:
            size = random.randint(mppl, n - lines * mppl)

        n -= size
        yield size


# generate a random orientation of a line with n points
def line_orientation(n):
    maxk = int(2 * maxx / n)

    dy = random.randint(-maxk, maxk)

    if dy == 0:
        dx = 1
    else:
        dx = random.randint(0, maxk)

    if dx == 0:
        dy = 1

    return (dx, dy)


# Generate points
points = set()
for n_points in line_size(n, lines):
    (dx, dy) = line_orientation(n_points)

    cx = random.randint(-maxx, maxx)
    cy = random.randint(-maxx, maxx)

    line_points = { (cx, cy) }

    i = 0
    while len(line_points) < n_points and i < n_points * 10:
        i += 1
        
        t = random.randint(-n_points, n_points)

        px = cx + t * dx
        py = cy + t * dy

        if abs(px) <= maxx and abs(py) <= maxx:
            line_points.add((px, py))

    points.update(line_points)

print(len(points))

for (px, py) in points:
    print(px, py)
