def get_arg(program, mode, argN):
    m = mode % 10
    res = 0
    if m == 0:
        res = program[program[argN]]
    elif m== 1:
        res = program[argN]
    else:
        print("Invalid mode " + str(mode))
        exit()
    return (res, mode // 10)

def run_program(p, inp):
    program = p[:]
    output = []

    i = 0
    while program[i] != 99:
        instruction = program[i]
        opcode = instruction % 100
        mode = instruction // 100
        if opcode == 1: # Add
            arg1, mode = get_arg(program, mode, i+1)
            arg2, mode = get_arg(program, mode, i+2)
            arg3 = program[i+3]
            program[arg3] = arg1 + arg2
            i += 4
        elif opcode == 2: # Multiply
            arg1, mode = get_arg(program, mode, i+1)
            arg2, mode = get_arg(program, mode, i+2)
            arg3 = program[i+3]
            program[arg3] = arg1 * arg2
            i += 4
        elif opcode == 3: # Input
            arg1 = program[i+1]
            program[arg1] = inp
            i += 2
        elif opcode == 4: # Output
            arg1, mode = get_arg(program, mode, i+1)
            output.append(arg1)
            i += 2
        elif opcode == 5: # Jump if
            arg1, mode = get_arg(program, mode, i+1)
            arg2, mode = get_arg(program, mode, i+2)
            if arg1 != 0:
                i = arg2
            else:
                i += 3
        elif opcode == 6: # Jump if not
            arg1, mode = get_arg(program, mode, i+1)
            arg2, mode = get_arg(program, mode, i+2)
            if arg1 == 0:
                i = arg2
            else:
                i += 3
        elif opcode == 7: # Less than
            arg1, mode = get_arg(program, mode, i+1)
            arg2, mode = get_arg(program, mode, i+2)
            arg3 = program[i+3]
            if arg1 < arg2:
                program[arg3] = 1
            else:
                program[arg3] = 0
            i += 4
        elif opcode == 8: # Equal
            arg1, mode = get_arg(program, mode, i+1)
            arg2, mode = get_arg(program, mode, i+2)
            arg3 = program[i+3]
            if arg1 == arg2:
                program[arg3] = 1
            else:
                program[arg3] = 0
            i += 4
        else:
            print("Invalid opcode " + str(opcode))
            exit()
    return (program[0], output)


f = open("../inp/5.in", "r")
data = f.read().strip()
f.close()
program = [int(x) for x in data.split(",")]
print(run_program(program, 1)[1])
print(run_program(program, 5)[1])
