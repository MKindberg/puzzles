import functools
f = open("../inp/8.in", "r")
data = f.read().strip()
f.close()

layers = [data[i:i+6*25] for i in range(0, len(data), 6*25)]

nums = [(x.count('0'), x.count('1'), x.count('2')) for x in layers]
m = min(nums, key = lambda x: x[0])
print(m[1]*m[2])

image = functools.reduce(lambda acc, e: [x[1] if x[0] == "2" else x[0] for x in zip(acc, e)], layers)
for i in range(6):
    for j in range(25):
        pixel = 'x' if image[j + i*25] == '1' else ' '
        print(pixel, end='')
    print()
