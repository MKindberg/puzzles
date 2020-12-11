def inc_adj(_, count, i, j, k, l):
    if k == 0 and l == 0:
        return
    count[i+k][j+l] += 1

def inc_seen(seats, count, y, x, dirY, dirX):
    height = len(seats)
    width = len(seats[0])
    if dirY == 0 and dirX == 0:
        return
    y += dirY
    x += dirX
    while y >= 0 and y < height and x >= 0 and x < width:
        if seats[y][x] != '.':
            count[y][x] += 1
            break
        y += dirY
        x += dirX

def count_occupied(seats, inc):
    height = len(seats)
    width = len(seats[0])
    count = [[0 for i in range(width)] for j in range(height)]
    for i in range(1, height-1):
        for j in range(1, width-1):
            if seats[i][j] == "#":
                for k in range(-1, 2):
                    for l in range(-1, 2):
                        inc(seats, count, i, j, k, l)
    return count

def sum_occupied(seats):
    return sum([x.count("#") for x in seats])

def find_equilibrium(data, inc, limit):
    height = len(data)
    width = len(data[0])
    seats = [list('.' * (width+2))] + [['.'] + row[:] + ['.'] for row in data] + [list('.' * (width+2))] # Add a buffer around the matrix to get rid of a lot of ifs in the code
    changed = True
    while changed:
        changed = False
        count = count_occupied(seats, inc)

        for i in range(1, height+1):
            for j in range(1, width+1):
                if seats[i][j] == 'L' and count[i][j] == 0:
                    seats[i][j] = '#'
                    changed = True
                elif seats[i][j] == '#' and count[i][j] >= limit:
                    seats[i][j] = 'L'
                    changed = True
    return sum_occupied(seats)

f = open("11.in", "r")
data = [list(x) for x in f.read().strip().splitlines()]
f.close()

print(find_equilibrium(data, inc_adj, 4))
print(find_equilibrium(data, inc_seen, 5))
