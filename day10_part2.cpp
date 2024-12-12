#include <bits/stdc++.h>

using namespace std;

const int MAX = 128;

int n, m, score;
int grid[MAX][MAX];
long long memo[MAX][MAX];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

long long dfs(int i, int j) {
    if (grid[i][j] == 9) {
        return memo[i][j] = 1;
    }

    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    long long score = 0;

    for (int d = 0; d < 4; d++) {
        int it = i + dx[d];
        int jt = j + dy[d];

        if (it >= 0 && it < n && jt >= 0 && jt < m && grid[it][jt] == grid[i][j] + 1) {
            score += dfs(it, jt);
        }
    }

    return memo[i][j] = score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(memo, -1, sizeof(memo));

    n = 57;
    m = 57;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            grid[i][j] = c - '0';
        }
    }

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                ans += dfs(i, j);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}