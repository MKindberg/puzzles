import functools
import math

def calcSeat(acc, c):
    if c == 'B':
        min = acc[0][0]
        max = acc[0][1]
        row = (math.ceil((min + max) / 2), max)
        col = acc[1]
    elif c == 'F':
        min = acc[0][0]
        max = acc[0][1]
        row = (min, (min + max) // 2)
        col = acc[1]
    elif c == 'R':
        min = acc[1][0]
        max = acc[1][1]
        col = (math.ceil((min + max) / 2), max)
        row = acc[0]
    elif c == 'L':
        min = acc[1][0]
        max = acc[1][1]
        col = (min, (min + max) // 2)
        row = acc[0]
    return (row, col)


def seatID(seat):
    ((row, _), (col, _)) = functools.reduce(calcSeat, seat, ((0, 127), (0, 7)))
    return row * 8 + col

def diff2(acc, seatID):
    if(seatID - acc > 1):
        return acc
    return seatID

f = open("inp5.txt", "r")
seats = f.read().split("\n")[:-1]
f.close()

seatIDs = sorted(list(map(seatID, seats)))
print(seatIDs[-1])

print(functools.reduce(diff2, seatIDs, seatIDs[0]) + 1)
