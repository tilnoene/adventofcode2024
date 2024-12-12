#include <bits/stdc++.h>

using namespace std;

const int MAX = 128;

int n, m, score;
int grid[MAX][MAX];
bool visited[MAX][MAX];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int i, int j) {
    visited[i][j] = true;
    
    if (grid[i][j] == 9) {
        score++;
        return;
    }

    for (int d = 0; d < 4; d++) {
        int it = i + dx[d];
        int jt = j + dy[d];

        if (it >= 0 && it < n && jt >= 0 && jt < m && !visited[it][jt] && grid[it][jt] == grid[i][j] + 1) {
            dfs(it, jt);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    n = 57;
    m = 57;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            grid[i][j] = c - '0';
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                score = 0;
                memset(visited, 0, sizeof(visited));

                dfs(i, j);

                ans += score;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}