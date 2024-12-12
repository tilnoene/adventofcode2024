n = 850

def concat(a, b):
    return int(f'{a}{b}')

def solve(index, expression, numbers, wanted):
    if index >= len(numbers):
        return eval(expression) == wanted
    
    answer = False

    if answer > wanted:
      return False

    answer |= solve(index + 1, f'{expression} * {numbers[index]}', numbers, wanted)
    answer |= solve(index + 1, f'({expression} + {numbers[index]})', numbers, wanted)
    answer |= solve(index + 1, f'(concat({expression}, {numbers[index]}))', numbers, wanted)

    return answer

answer = 0

for i in range(n):
    line = input().split(': ')
    wanted = int(line[0])

    numbers = [int(x) for x in line[1].split()]

    if solve(1, f'{numbers[0]}', numbers, wanted):
        answer += wanted

print(answer)