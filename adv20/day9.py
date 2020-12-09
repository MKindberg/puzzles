
def is_sum(previous, num):
    for i in range(0, len(previous) - 1):
        for j in range(i+1, len(previous)):
            if previous[i] + previous[j] == num:
                return True
    return False

f = open("inp9.txt", "r")
data = [int(x) for x in f.read().strip().splitlines()]
f.close()

invalid = 0
for i in range(25, len(data)):
    if not is_sum(data[i-25:i], data[i]):
        invalid = data[i]
        break
print(invalid)

nums = [data[0]]
s = data[0]
i = 1
while s != invalid:
    if s < invalid:
        nums.append(data[i])
        s += data[i]
        i+=1
    elif s > invalid:
        s -= nums.pop(0)

print(min(nums) + max(nums))

