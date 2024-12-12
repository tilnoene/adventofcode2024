want = 'XMAS'

n = 140

grid = []

for i in range(n):
    grid.append(input())

m = len(grid[0])

ans = 0

for i in range(1, n - 1):
    for j in range(1, m - 1):
        if grid[i][j] == 'A':
            s1 = [grid[i - 1][j - 1], 'A', grid[i + 1][j + 1]]
            s2 = [grid[i - 1][j + 1], 'A', grid[i + 1][j - 1]]

            s1.sort()
            s2.sort()

            if s1 == list('AMS') and s2 == list('AMS'):
                ans += 1

print(ans)