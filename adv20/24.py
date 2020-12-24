import re

f = open("24.in", "r")
data = f.read().strip().splitlines()
f.close()

pattern = "(ne|nw|se|sw|e|w)"
directions = {"ne":(1, 0.5), "nw":(1, -0.5), "se": (-1, 0.5), "sw": (-1, -0.5), "e": (0, 1), "w": (0, -1)}
tiles = {}

for l in data:
    current = (0, 0)
    for d in re.findall(pattern, l):
        current = (current[0]+directions[d][0], current[1]+directions[d][1])
    tiles[current] = (tiles.get(current, 0) + 1) % 2
    
print(sum(tiles.values()))
neighbours = {}

days = 100
for i in range(days):
    neighbours = {}
    # Count neighbours
    for k in tiles:
        neighbours[k] = neighbours.get(k, 0)
        for d in directions.values():
            t = (k[0]+d[0], k[1]+d[1])
            if tiles[k] == 1:
                neighbours[t] = neighbours.get(t, 0) + 1

    # Turn tiles
    for k in neighbours:
        if tiles.get(k, 0) == 1 and neighbours[k] == 0 or neighbours[k] > 2:
            tiles[k] = 0
        elif tiles.get(k, 0) == 0 and neighbours[k] == 2:
            tiles[k] = 1

print(sum(tiles.values()))
