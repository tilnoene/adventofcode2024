a = []
cnt = {}

for i in range(1000):
  line = input().split('   ')

  a.append(int(line[0]))
  
  b = int(line[1])
  cnt[b] = cnt.get(b, 0) + 1

total_sum = 0

for i in range(len(a)):
  total_sum += a[i] * cnt.get(a[i], 0)

print(total_sum)