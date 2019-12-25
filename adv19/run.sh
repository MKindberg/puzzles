#!/bin/bash

day=$1
name=day${day}
flags="-g -lm -o ${name} -Wall -Wextra -Werror"
input=input.txt
gcc day${day}.c ${flags} && ./${name}.out ${input}
