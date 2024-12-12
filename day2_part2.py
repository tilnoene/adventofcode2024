def safe(numbers):
    if numbers != sorted(numbers) and numbers != sorted(numbers, reverse=True):
        return False
  
    for i in range(1, len(numbers)):
        diff = abs(numbers[i] - numbers[i - 1])

        if diff < 1 or diff > 3:
            return False
    
    return True

answer = 0

for i in range(1000):
    numbers = [int(x) for x in input().split()]

    if safe(numbers):
        answer += 1

print(answer)