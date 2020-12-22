def play(p1, p2):
    while len(p1) > 0 and len(p2) > 0:
        c1 = p1.pop(0)
        c2 = p2.pop(0)
        if c1 > c2:
            p1 += [c1, c2]
        else:
            p2 += [c2, c1]
    return p1 if len(p1) > 0 else p2

def play_rec(p1, p2, depth):
    played = {}
    while len(p1) > 0 and len(p2) > 0:
        if (p1, p2) in played.get((p1[0], p2[0]), []):
            return (1, p1)
        else:
            played[(p1[0], p2[0])] = played.get((p1[0], p2[0]), [])+[(p1[:], p2[:])]
        c1 = p1.pop(0)
        c2 = p2.pop(0)
        w = 0
        if c1 <= len(p1) and c2 <= len(p2):
            w, _ = play_rec(p1[:c1], p2[:c2], depth+1)
        if w == 1 or w ==0 and c1 > c2:
            p1 += [c1, c2]
        else:
            p2 += [c2, c1]

    return (1, p1) if len(p1) > 0 else (2, p2)


f = open("22.in", "r")
data = f.read().strip().split('\n\n')
f.close()

p1 = [int(x) for x in data[0].splitlines()[1:]]
p2 = [int(x) for x in data[1].splitlines()[1:]]


w = play(p1[:], p2[:])
score = sum(map(lambda x: x[0]*x[1], zip(w, range(len(w), 0, -1))))
print(score)

_, w = play_rec(p1[:], p2[:], 0)
score = sum(map(lambda x: x[0]*x[1], zip(w, range(len(w), 0, -1))))
print(score)
