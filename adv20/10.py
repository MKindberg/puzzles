f = open("10.in", "r")
data = [int(x) for x in f.read().strip().splitlines()]
f.close()

adapt = [0] + sorted(data)
diffs = [0] * 4
for i in range(1, len(adapt)):
    diffs[adapt[i] - adapt[i-1]] += 1

diffs[3] += 1
print(diffs[1] * diffs[3])

comb = [0] * len(adapt)
comb[0] = 1
for i in range(1, len(adapt)):
    j = 1
    while i-j >= 0 and adapt[i] - adapt[i-j] <= 3:
        comb[i] += comb[i-j]
        j += 1
print(comb[-1])
