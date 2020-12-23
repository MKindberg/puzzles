
def extract3(cups, current):
    n = current
    e = []
    for _ in range(3):
        n = cups[n]
        e.append(n)
    cups[current] = cups[n]
    return e
def insert3(cups, dest, picked):
    n = cups[dest]
    cups[dest] = picked[0]
    cups[picked[2]] = n

def play(cups, rounds, maxC, start):

    current = start
    picked = None

    for _ in range(rounds):
        picked = extract3(cups, current)
        dest = current-1 if current > 1 else maxC
        while dest in picked:
            dest = dest-1 if dest > 1 else maxC
        insert3(cups, dest, picked)
        current = cups[current]
    return cups

data = [int(x) for x in list("364289715")]
cups = [x+1 for x in range(len(data)+1)]
for i in range(len(data)-1):
    cups[data[i]] = data[i+1]
cups[data[-1]] = data[0]

cups = play(cups, 10, 9, data[0])
i = 1
while cups[i] != 1:
    print(cups[i], end='')
    i = cups[i]
print()

cups = [x+1 for x in range(1000001)]
for i in range(len(data)-1):
    cups[data[i]] = data[i+1]
cups[-1] = data[0]
cups[data[-1]] = 10

cups = play(cups, 10000000, 1000000, data[0])
print(cups[1]*cups[cups[1]])
