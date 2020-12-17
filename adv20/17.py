import numpy as np

def inc_adj(count, z, y, x):
    for zi in [-1, 0, 1]:
        for yi in [-1, 0, 1]:
            for xi in [-1, 0, 1]:
                if xi == yi and yi == zi and zi == 0:
                    continue
                count[z+zi][y+yi][x+xi] += 1
    return count

def inc_adj4(count, w, z, y, x):
    for wi in [-1, 0, 1]:
        for zi in [-1, 0, 1]:
            for yi in [-1, 0, 1]:
                for xi in [-1, 0, 1]:
                    if xi == yi and yi == zi and zi == wi and wi == 0:
                        continue
                    count[w+wi][z+zi][y+yi][x+xi] += 1
    return count

def count_neighbours(matrix):
    nZ = len(matrix)
    nY = len(matrix[0])
    nX = len(matrix[0][0])
    count = np.zeros((nZ, nX, nY))
    for z in range(nZ):
        for y in range(nY):
            for x in range(nX):
                if matrix[z][y][x] == 1:
                    count = inc_adj(count, z, y, x)
    return count

def count_neighbours4(matrix):
    nW = len(matrix)
    nZ = len(matrix[0])
    nY = len(matrix[0][0])
    nX = len(matrix[0][0][0])
    count = np.zeros((nW, nZ, nX, nY))
    for w in range(nW):
        for z in range(nZ):
            for y in range(nY):
                for x in range(nX):
                    if matrix[w][z][y][x] == 1:
                        count = inc_adj4(count, w, z, y, x)
    return count

def run4(matrix, gen):
    nW = len(matrix)
    nZ = len(matrix[0])
    nY = len(matrix[0][0])
    nX = len(matrix[0][0][0])

    for i in range(gen):
        count = count_neighbours4(matrix)
        for w in range(nW):
            for z in range(nZ):
                for y in range(nY):
                    for x in range(nX):
                        if matrix[w][z][y][x] == 1 and (count[w][z][y][x] == 2 or count[w][z][y][x] == 3):
                            matrix[w][z][y][x] = 1
                        elif matrix[w][z][y][x] == 0 and count[w][z][y][x] == 3:
                            matrix[w][z][y][x] = 1
                        else:
                            matrix[w][z][y][x] = 0

    return matrix

def run(matrix, gen):
    nZ = len(matrix)
    nY = len(matrix[0])
    nX = len(matrix[0][0])

    for i in range(gen):
        count = count_neighbours(matrix)
        for z in range(nZ):
            for y in range(nY):
                for x in range(nX):
                    if matrix[z][y][x] == 1 and (count[z][y][x] == 2 or count[z][y][x] == 3):
                        matrix[z][y][x] = 1
                    elif matrix[z][y][x] == 0 and count[z][y][x] == 3:
                        matrix[z][y][x] = 1
                    else:
                        matrix[z][y][x] = 0

    return matrix

f = open("17.in", "r")
data = [list(x) for x in f.read().strip().splitlines()]
f.close()

i_nX = len(data[0])
i_nY = len(data)
i_nZ = 1

nX = i_nX + 12
nY = i_nY + 12
nZ = i_nZ + 12

matrix = np.zeros((nZ, nY, nX))

for y in range(i_nY):
    for x in range(i_nX):
        matrix[6][y+6][x+6] = 1 if data[y][x] == '#' else 0

matrix = run(matrix, 6)
print(np.sum(matrix))
nW = 13
matrix = np.zeros((nW, nZ, nY, nX))

for y in range(i_nY):
    for x in range(i_nX):
        matrix[6][6][y+6][x+6] = 1 if data[y][x] == '#' else 0

matrix = run4(matrix, 6)

print(np.sum(matrix))
