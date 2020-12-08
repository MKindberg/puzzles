import functools

def calc_fuel(acc, mass):
    fuel = mass//3 - 2
    additional = fuel//3 - 2

    while additional > 0:
        fuel += additional
        additional = additional//3 - 2
    return acc + fuel

f = open("../inp/day1.txt", "r")
data = f.read().strip()
f.close()

modules = list(map(int, data.split("\n")))

fuel = functools.reduce(lambda acc, x: acc + x//3 -2, modules, 0)
print(fuel)

fuel = functools.reduce(calc_fuel, modules, 0)
print(fuel)
