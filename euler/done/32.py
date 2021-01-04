import itertools

prods = set()
for i in [1, 2]:
    for p in itertools.permutations('123456789', 5):
        p = ''.join(p)
        n = str(int(p[:i]) * int(p[i:]))
        if len(n) == 4 and set('123456789').difference(p).difference(n) == set():
            print(p[:i], p[i:], n)
            prods.add(int(n))

print(len(prods))
print(sum(prods))
