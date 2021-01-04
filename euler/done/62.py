cubes = {}
i = 100
while True:
    c = i**3
    key = ''.join(sorted(str(c)))
    cubes[key] = cubes.get(key, []) + [c]
    if len(cubes[key]) == 5:
        print(cubes[key])
        break
    i += 1
