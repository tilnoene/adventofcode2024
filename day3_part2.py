import re

def mul(a, b):
    return a * b

answer = 0

can = True

for i in range(6):
    line = input()

    groups = re.findall("mul\(\d+,\d+\)|don't\(\)|do\(\)", line)

    for group in groups:
        if group == 'do()':
            can = True
        elif group == 'don\'t()':
            can = False
        else:
            if can:
                answer += eval(group)
    
print(answer)