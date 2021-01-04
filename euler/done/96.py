from copy import deepcopy
def in_col(s, col, n):
    for i in range(9):
        if s[i][col] == n:
            return True
    return False

def in_square(s, row, col, n):
    for r in range(row//3*3, row//3*3+3):
        for c in range(col//3*3, col//3*3+3):
            if s[r][c] == n:
                return True
    return False

def solve(sudoku, row, col):
    if col == 9:
        return solve(sudoku, row+1, 0)
    if row == 9:
        return True, sudoku
    s = deepcopy(sudoku)
    if s[row][col] != 0:
        return solve(s, row, col+1)
    for i in range(1, 10):
        if not (i in s[row] or in_col(s, col, i) or in_square(s, row, col, i)):
            s[row][col] = i
            res, s2 = solve(s, row, col+1)
            if res:
                return True, s2
    return False, None


f = open("sudoku.txt", "r")
data = f.read().strip().splitlines()
f.close()
count = 0
for i in range(len(data)//10):
    print(i)
    s = data[i*10+1:i*10+10]
    sudoku = [list(map(int, list(x))) for x in s]
    res, solved = solve(sudoku, 0, 0)
    if res:
        count += solved[0][0]*100 + solved[0][1]*10 + solved[0][2]
    else:
        print("Error")

print(count)
