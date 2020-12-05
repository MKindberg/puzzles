import functools

def calcTrees(treeMap, steps):
    width = len(treeMap[0])
    return functools.reduce(lambda acc, row: ((acc[0] + steps[0]) % width, acc[1] + 1) if row[acc[0]] == "#" else ((acc[0] + steps[0]) % width, acc[1]), treeMap[::steps[1]], (0,  0))[1]

f = open("inp3.txt", "r")
treeMap = f.read().split("\n")[:-1]

paths = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]

trees = list(map(lambda x: calcTrees(treeMap, x), paths))
print(*list(zip(paths, trees)), sep="\n")

print(functools.reduce(lambda acc, x: acc*x, trees, 1))
