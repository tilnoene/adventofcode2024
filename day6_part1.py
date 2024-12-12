import sys
sys.setrecursionlimit(10**5)

n = 130

grid = []

for i in range(n):
    grid.append(input())

m = len(grid[0])

dx = [-1, 0, 1, 0]:
dy = [0, 1, 0, -1]

visited = []

for i in range(m):
    visited.append([])

    for j in range(m):
        visited[-1].append([False, False, False, False])

def dfs(i, j, direction):
    visited[i][j][direction] = True

    it = i + dx[direction]
    jt = j + dy[direction]

    if it < 0 or it >= n or jt < 0 or jt >= m:
        return
    
    if grid[it][jt] == '#':
        newdir = (direction + 1) % 4

        if not visited[i][j][newdir]:
            dfs(i, j, newdir)
    else:
        if not visited[it][jt][direction]:
            dfs(it, jt, direction)

it = 0
jt = 0
direction = 0 # ^

for i in range(n):
    for j in range(m):
        if grid[i][j] != '.' and grid[i][j] != '#':
            it = i
            jt = j

dfs(it, jt, direction)

ans = 0

for i in range(n):
    for j in range(m):
        if True in visited[i][j]:
            ans += 1

print(ans)