import time
numbers = [0,12,6,13,20,1,17]

def solve(numbers, length): # Slow but memory efficient
    last_spoken = {}
    for i in range(len(numbers)):
        last_spoken[numbers[i]] = i

    num = 0
    for i in range(len(numbers), length-1):
        num2 = i - last_spoken.get(num, i) 
        last_spoken[num] = i
        num = num2

    return num

# A lot faster since a dict has to do hashing but an array of 30.000.000 seems wasteful
def solve2(numbers, length):
    last_spoken = [-1] * length
    for i in range(len(numbers)):
        last_spoken[numbers[i]] = i

    num = 0
    for i in range(len(numbers), length-1):
        if num > len(last_spoken):
            last_spoken += (num -len(last_spoken)+1) * [-1]
        num2 = i - last_spoken[num] if last_spoken[num] != -1 else 0
        last_spoken[num] = i
        num = num2

    return num

print(solve(numbers, 2020))

print(solve2(numbers, 30000000))
