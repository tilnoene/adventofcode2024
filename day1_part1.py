a = []
b = []

for i in range(1000):
  line = input().split('   ')

  a.append(int(line[0]))
  b.append(int(line[1]))

a.sort()
b.sort()

total_sum = 0

for i in range(len(a)):
  total_sum += abs(a[i] - b[i])

print(total_sum)