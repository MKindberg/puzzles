f = open("inp6.txt", "r")
groups = f.read().split("\n\n")
f.close()

print(sum(list(map(lambda x: len(set(x.replace('\n', ''))), groups))))

print(sum(list(map(lambda x: len(set(x.split("\n")[0]).intersection(*x.strip().split("\n"))), groups))))
