n = 103
m = 101

cnt = []
robots = []

for i in range(n):
	cnt.append([0] * m)

while True:
	try:
		line = input().split()

		pj, pi = map(int, line[0].split('=')[1].split(','))
		vj, vi = map(int, line[1].split('=')[1].split(','))

		robots.append([ pi, pj, vi, vj ])

		cnt[pi][pj] += 1
	except:
		break

def walk_all_robots():
	for i in range(len(robots)):
		pi, pj, vi, vj = robots[i]

		cnt[pi][pj] -= 1

		pi = (pi + vi + n) % n
		pj = (pj + vj + m) % m

		cnt[pi][pj] += 1

		robots[i] = [pi, pj, vi, vj]

def print_map():
	for i in range(n):
		for j in range(m):
			if cnt[i][j] == 0:
				print('.', end='')
			else:
				print(cnt[i][j], end='')
		print()

def valid():
	for i in range(n):
		for j in range(m):
			if cnt[i][j] > 1:
				return False

	return True

for i in range(8000):
	walk_all_robots()

	if valid():
		print(i)
		print_map()
