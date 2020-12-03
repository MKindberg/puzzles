f = open("inp3.txt", "r")
map = f.read().split("\n")[:-1]

width = len(map[0])
height = len(map)

paths = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]
tree_prod = 1
for p in paths:
    x = 0
    y = 0
    trees = 0
    while y < height:
        if map[y][x % width] == "#":
            trees += 1
        x += p[0]
        y += p[1]
    tree_prod *= trees
    print("{} Right, {} Down: {} Trees".format(p[0], p[1], trees))

print(tree_prod)
