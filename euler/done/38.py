m = 0
for i in range(1, 10000):
    for j in range(2, 10):
        s = ''.join([str(i*y) for y in range(1, j+1)])
        if len(s) == 9 and set('123456789').difference(s) == set() and int(s) > m:
            m = int(s)
            break
        elif len(s) >= 9:
            break

print(m)

