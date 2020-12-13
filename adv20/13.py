import math

f = open("13.in", "r")
data = f.read().strip().splitlines()
f.close()

time = int(data[0])
busses = zip(data[1].split(","), range(len(data[1].split(","))))
busses = [(int(bus[0]), bus[1]) for bus in busses if bus[0] != 'x']

wait_times = [(bus[0] - (time % bus[0]), bus[0]) for bus in busses]
shortest_time, best_bus = min(wait_times, key=lambda x: x[0])
print(best_bus*shortest_time)

n = [bus[0] for bus in busses]
N = math.prod(n)
y = [N//x for x in n]
a = [-bus[1] for bus in busses]
z = [list(filter(lambda x: (x*N//m) % m == 1, range(m)))[0] for m in n]

print(sum([math.prod([y[i], a[i], z[i]]) for i in range(len(n))]) % N)

