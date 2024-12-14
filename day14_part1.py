n = 103
m = 101

SECONDS = 100
cnt = []

for i in range(n):
	cnt.append([0] * m)

while True:
	try:
		line = input().split()

		pj, pi = map(int, line[0].split('=')[1].split(','))
		vj, vi = map(int, line[1].split('=')[1].split(','))

		for i in range(SECONDS):
			pi = (pi + vi + n) % n
			pj = (pj + vj + m) % m
		
		cnt[pi][pj] += 1
	except:
		break

answer = 1

for it in range(0, n, (n + 1) // 2):
	for jt in range(0, m, (m + 1) // 2):
		soma = 0

		for i in range(it, it + n // 2):
			for j in range(jt, jt + m // 2):
				soma += cnt[i][j]
		
		answer *= soma

print(answer)

# for i in range(n):
# 	for j in range(m):
# 		if cnt[i][j] == 0:
# 			print('.', end='')
# 		else:
# 			print(cnt[i][j], end='')
		
# 	print()