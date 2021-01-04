from functools import reduce
f = open("keylog.txt", "r")
keys = f.read().strip().splitlines()
f.close()
precedes = [set() for _ in range(10)]
all_d = set()

for k in keys:
    precedes[int(k[0])].add(k[1])
    precedes[int(k[0])].add(k[2])
    precedes[int(k[1])].add(k[2])
    all_d.add(k[0])
    all_d.add(k[1])
    all_d.add(k[2])

key = []
while reduce(lambda x, y: x.union(y), precedes, set()) != set():
    for i in range(10):
        d = str(i)
        if d in all_d and precedes[i] == set():
            key.insert(0, d)
            all_d.remove(d)
            precedes = list(map(lambda x: x.difference(d), precedes))

