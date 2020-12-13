import itertools

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

def run_program(p, inp, first_inst = 0, first_inp = 0, reset = True):
    if reset:
        program = p[:]
    else:
        program = p
    output = inp[-1]

    inp_count = first_inp
    i = first_inst
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
            if inp_count > 1:
                return (i, output)
            program[arg1] = inp[inp_count]
            inp_count += 1
            i += 2
        elif opcode == 4: # Output
            arg1, mode = get_arg(program, mode, i+1)
            output = arg1
            i += 2
            return (i, output)
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
    return (-1, output)

def run_amplifiers(program, phase_setting):
    output = 0
    for p in phase_setting:
        _, output = run_program(program, [p, output])
    return output

def loop_amplifiers(program, phase_setting):
    programs = [program[:] for i in range(len(phase_setting))]
    current = [0, 0, 0, 0, 0] 
    output = 0
    first_inp = 0
    while current[-1] != -1:
        for i in range(len(phase_setting)):
            current[i], output = run_program(programs[i], [phase_setting[i], output], current[i], first_inp, False)
        first_inp = 1
    return output

f = open("../inp/7.in", "r")
data = f.read().strip()
f.close()
program = [int(x) for x in data.split(",")]

max_thrust = 0
phase_settings = itertools.permutations([0, 1, 2, 3, 4])
for p in phase_settings:
    thrust = run_amplifiers(program, p)
    if thrust > max_thrust:
        max_thrust = thrust
print(max_thrust)

phase_settings = itertools.permutations([5, 6, 7, 8, 9])
for p in phase_settings:
    thrust = loop_amplifiers(program, p)
    if thrust > max_thrust:
        max_thrust = thrust
print(max_thrust)
