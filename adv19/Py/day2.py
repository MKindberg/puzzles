
def run_program(p, start_vals):
    program = p[:]
    program[1:3] = start_vals

    i = 0
    while program[i] != 99:
        if program[i] == 1:
            arg1 = program[i+1]
            arg2 = program[i+2]
            arg3 = program[i+3]
            program[arg3] = program[arg1] + program[arg2]
            i += 4
        elif program[i] == 2:
            arg1 = program[i+1]
            arg2 = program[i+2]
            arg3 = program[i+3]
            program[arg3] = program[arg1] * program[arg2]
            i += 4
        else:
            print("Error!")
            return (1, 0)
    return (0, program[0])


f = open("../inp/day2.txt", "r")
data = f.read().strip()
f.close()

program = list(map(int, data.split(",")))
print(program[2])
print(run_program(program, [12, 2])[1])
print(program[2])

for noun in range(0, 100):
    for verb in range(0, 100):
        if run_program(program, [noun, verb]) == (0, 19690720):
            print(100 * noun + verb)
            exit(0)
