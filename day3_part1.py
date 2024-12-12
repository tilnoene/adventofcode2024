import re

def mul(a, b):
    return a * b

answer = 0

for i in range(6):
    line = input()

    groups = re.findall("mul\(\d+,\d+\)", line)

    for group in groups:
        answer += eval(group)
    
print(answer)