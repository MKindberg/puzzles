import re
f = open("21.in", "r")
data = f.read().strip().splitlines()
f.close()

pattern = "^(.+) \(contains (.+)\)$"

foods = []
allergens = {}
for r in data:
    m = re.match(pattern, r)
    foods.append(m.group(1).split())
    contains = m.group(2).split(', ')
    for c in contains:
        allergens[c] = allergens.get(c, set(foods[-1])).intersection(foods[-1])

all_allergens = set()
for v in allergens.values():
    all_allergens.update(v)
ingedients = set()
ingedients.update(*foods)
s = 0
for i in ingedients.difference(all_allergens):
    for f in foods:
        if i in f:
            s+=1
print(s)

for _ in range(len(allergens)):
    for k1 in allergens:
        for k2 in allergens:
            if k1 != k2 and len(allergens[k1]) == 1:
                allergens[k2] = allergens[k2].difference(allergens[k1])

for k in sorted(allergens.keys()):
    print(list(allergens[k])[0], end=',')
