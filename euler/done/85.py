limit = 2000000
def count_rect(height, width):
    tot = 0
    for h in range(1, height+1):
        for w in range(1, width+1):
            tot += (height-h+1)*(width-w+1)
    return tot

assert count_rect(2, 3) == count_rect(3, 2) == 18

width = 1
height = 1
count = 0
best = [0, 0, 0]
while count < limit:
    while width < height and count < limit:
        width += 1
        count = count_rect(height, width)
        if abs(best[0]-limit) > abs(count-limit):
            best[0] = count
            best[1] = width
            best[2] = height
    height += 1
    width = 1
    count = count_rect(height, width)
    if abs(best[0]-limit) > abs(count-limit):
        best[0] = count
        best[1] = width
        best[2] = height

print(best, best[1]*best[2])
