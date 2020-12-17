import itertools
import numpy as np

def loop(args, size, func):
    index = [0]*len(size)
    while True:
        func(*args, tuple(index))
        index[0] += 1
        for i in range(len(size)-1):
            if index[i] == size[i]:
                index[i] = 0
                index[i+1] += 1
        if index[-1] == size[-1]:
            break

def inc_adj(matrix, count, index):
    if matrix[index] == 1:
        zeros = (0,) * len(index)
        for i in itertools.product([-1, 0, 1], repeat=len(index)):
            if i != zeros:
                idx = tuple([sum(x) for x in zip(i, index)])
                count[idx] += 1
    return count

def count_neighbours(matrix, size):
    count = np.zeros(size)
    loop([matrix, count], size, inc_adj)
    return count

def generation(matrix, count, index):
    if matrix[index] == 1 and (count[index] == 2 or count[index] == 3):
        matrix[index]= 1
    elif matrix[index] == 0 and count[index] == 3:
        matrix[index] = 1
    else:
        matrix[index] = 0

def run(matrix, size, gen):
    for i in range(gen):
        count = count_neighbours(matrix, size)
        loop([matrix, count], size, generation)

    return matrix

f = open("17.in", "r")
data = [list(x) for x in f.read().strip().splitlines()]
f.close()

i_nX = len(data[0])
i_nY = len(data)

# Part 1
nX = i_nX + 12
nY = i_nY + 12
nZ = 13
size = (nZ, nY, nX)
matrix = np.zeros(size)

for y in range(i_nY):
    for x in range(i_nX):
        matrix[6][y+6][x+6] = 1 if data[y][x] == '#' else 0

matrix = run(matrix, size, 6)
print(np.sum(matrix))

# Part 2
nW = 13
size = (nW, nZ, nY, nX)
matrix = np.zeros(size)

for y in range(i_nY):
    for x in range(i_nX):
        matrix[6][6][y+6][x+6] = 1 if data[y][x] == '#' else 0

matrix = run(matrix, size, 6)

print(np.sum(matrix))
