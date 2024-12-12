want = 'XMAS'

n = 140

grid = []

for i in range(n):
    grid.append(input())

m = len(grid[0])

ans = 0

dx = [0, 0, 1, -1, 1, 1, -1, -1]
dy = [1, -1, 0, 0, 1, -1, 1, -1]

def dfs(i, j, index_want, direction):
    global ans

    if index_want >= len(want) - 1:
        ans += 1
        return
    
    it = i + dx[direction]
    jt = j + dy[direction]

    if it >= 0 and it < n and jt >= 0 and jt < m and grid[it][jt] == want[index_want + 1]:
        dfs(it, jt, index_want + 1, direction)

for i in range(n):
    for j in range(m):
        if grid[i][j] == want[0]:
            for k in range(len(dx)):
                dfs(i, j, 0, k)

print(ans)