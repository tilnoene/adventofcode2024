n = 1176
exists = {}

def valid(numbers):
    for i in range(1, len(numbers)):
        for j in range(0, i):
            if exists.get(f'{numbers[i]}|{numbers[j]}', False):
                return False
    
    return True

for i in range(n):
    exists[input()] = True

input()

answer = 0

for i in range(1362 - 1178 + 1):
    numbers = [int(x) for x in input().split(',')]

    if valid(numbers):
        answer += numbers[len(numbers) // 2]

print(answer)