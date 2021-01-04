import math

f = open("base_exp.txt", "r")
numbers = [x.split(',') for x in f.read().strip().splitlines()]
f.close()

logarithms = [math.log(int(x[0]))*int(x[1]) for x in numbers]

print(logarithms.index(max(logarithms))+1)
