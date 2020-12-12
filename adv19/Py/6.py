def count_orbits(orbits, planet, level):
    return level + sum([count_orbits(orbits, x, level+1) for x in orbits.get(planet, [])])

def find_path(orbits, planet):
    return set([planet]).union(find_path(orbits, orbits[planet]) if planet in orbits else set())

f = open("../inp/6.in", "r")
data = [x.split(")") for x in f.read().strip().splitlines()]
f.close()

parents = {}
children = {}

for i in data:
    parent = i[0]
    child = i[1]
    parents[parent] = parents.get(parent, []) + [child]
    children[child] = parent

print(count_orbits(parents, "COM", 0))
path_san = find_path(children, "SAN")
path_you = find_path(children, "YOU")
print(len(path_san.symmetric_difference(path_you)) - 2)
