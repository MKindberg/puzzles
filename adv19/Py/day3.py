
def step_wire(instructions):
    wire = []
    x = 0
    y = 0
    s = 0
    for i in instructions.split(","):
        for steps in range(0, int(i[1:])):
            s+= 1
            if i[0] == 'R':
                x += 1
            elif i[0] == 'L':
                x -= 1
            elif i[0] == 'U':
                y += 1
            elif i[0] == 'D':
                y -= 1
            wire.append((x, y, s))
    return wire

def crossings(wire1, wire2):
    w1 = sorted(wire1, key=lambda x: abs(x[0]) + abs(x[1]))
    w2 = sorted(wire2, key=lambda x: abs(x[0]) + abs(x[1]))
    start2 = 0
    closest_crossing = 0
    min_steps = len(w1) + len(w1)
    for i in range(0, len(w1)):
        for j in range(start2, len(w2)):
            location1 = w1[i]
            location2 = w2[j]
            d1 = abs(location1[0]) + abs(location1[1])
            d2 = abs(location2[0]) + abs(location2[1])
            if location1[:2] == location2[:2]:
                if closest_crossing == 0:
                    closest_crossing = d1
                steps = location1[2] + location2[2]
                if steps < min_steps:
                    min_steps = steps
                break
            elif d2 > d1:
                break
            elif d1 > d2:
                start2 = j+1
    return (closest_crossing, min_steps)

f = open ("../inp/day3.txt", "r")
data = f.read().strip().split("\n")
f.close()
wire1 = step_wire(data[0])
wire2 = step_wire(data[1])

print(crossings(wire1, wire2))
