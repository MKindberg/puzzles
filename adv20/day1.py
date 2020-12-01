def findSum2(entries, s):
    for i in range(len(entries) - 1):
        for j in range(i+1, len(entries)):
            if(entries[i] + entries[j] == s):
                return entries[i]*entries[j]
            elif(entries[i] + entries[j] > s):
                break
    return -1

def findSum3(entries, s):
    for i in range(len(entries) - 1):
        for j in range(i+1, len(entries) - 2):
            if(entries[i] + entries[j] >= s):
                break
            for k in range(j+1, len(entries)):
                if(entries[i] + entries[j] + entries[k] == s):
                    return entries[i]*entries[j]*entries[k]
                elif(entries[i] + entries[j] + entries[k]> s):
                    break
    return -1

f = open("inp1.txt", "r")
entries = sorted(list(map(int, f.read().split('\n')[:-1])))
f.close()

print(findSum2(entries, 2020))
print(findSum3(entries, 2020))

