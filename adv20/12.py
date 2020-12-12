def boatRide(data, direction, f, r, u):
    directions = ["N", "E", "S", "W"]
    travel = {"N":0, "E":0, "S":0, "W":0}
    for i in data:
        action = i[0]
        value = int(i[1:])
        if action == 'F':
            travel = f(travel, directions, direction, value)
        elif action == 'L':
            direction = r(direction, directions, -value//90)
        elif action == 'R':
            direction = r(direction, directions, value//90)
        else:
            travel, direction = u(travel, direction, action, value)

    NS = travel["N"] - travel["S"]
    EW = travel["E"] - travel["W"]
    return abs(NS) + abs(EW)

f = open("12.in", "r")
data = f.read().strip().splitlines()
f.close()

#################### PT 1 ####################
def forward(travel, directions, d, value):
    travel[directions[d]] += value
    return travel

def rotate(direction, _, d):
    return (direction + d) % 4

def update(travel, d, action, value):
    travel[action] += value
    return (travel, d)

direction = 1
print(boatRide(data, direction, forward, rotate, update))

#################### PT 2 ####################
def forwardWp(travel, _, waypoint, value):
    for k in waypoint:
        travel[k] += value * waypoint[k]
    return travel

def rotateWp(waypoint, directions, d):
    wp2 = {}
    for k in waypoint:
        k_index = directions.index(k)
        k2_index = (k_index + d) % 4
        k2 = directions[k2_index]
        wp2[k2] = waypoint[k]
    return wp2

def updateWp(travel, waypoint, action, value):
    waypoint[action] += value
    return (travel, waypoint)

direction = {"N":1, "E":10, "S":0, "W":0}
print(boatRide(data, direction, forwardWp, rotateWp, updateWp))

