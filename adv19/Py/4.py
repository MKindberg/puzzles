import itertools

start = 372304
stop = 847060

matching1 = 0
matching2 = 0
i = start
while i < stop:
    s = str(i)
    for j in range(len(s)-1):
        if s[j] > s[j+1]:
            s = s[:j] + s[j] * len(s[j:])
            i = int(s)
            break
    else:
        groups = [list(group) for key, group in itertools.groupby(s)]
        if list(filter(lambda x: len(x) > 1, groups)) != []:
            matching1 += 1
        if list(filter(lambda x: len(x) == 2, groups)) != []:
            matching2 += 1
        i += 1

print(matching1)
print(matching2)

