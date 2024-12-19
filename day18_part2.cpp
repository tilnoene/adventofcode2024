#include <bits/stdc++.h>

using namespace std;

const int MAX = 80;
int n = 71;

char grid[MAX][MAX];
int dist[MAX][MAX];
bool visited[MAX][MAX];
pair<int, int> coord[4096];

int di[] = {0, 0, 1, -1};
int dj[] = {1, -1, 0, 0};

void bfs(int is, int js) {
    
    queue<pair<int, int>> q;

    dist[is][js] = 0;
    visited[is][js] = true;

    q.push({ is, js });

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int it = i + di[d];
            int jt = j + dj[d];

            if (it >= 0 && it < n && jt >= 0 && jt < n && !visited[it][jt] && grid[it][jt] == '.') {
                q.push({ it, jt });
                visited[it][jt] = true;
                dist[it][jt] = dist[i][j] + 1;
            }
        }
    }
}

void clear_grid() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            grid[i][j] = '.';
            visited[i][j] = false;
            dist[i][j] = -1;
        }
    }
}

bool f(int x) {
    clear_grid();

    for (int i = 0; i <= x; i++) {
        auto [it, jt] = coord[i];
        grid[jt][it] = '#';
    }

    bfs(0, 0);

    return !visited[n - 1][n - 1];
}

pair<int, int> first_true() {
    int lo = 0, hi = 3450;

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return coord[lo];
}

int main() {
    for (int i = 0; i < 3450; i++) {
        int it, jt; cin >> it >> jt;
        coord[i] = { it, jt };
    }

    auto ans = first_true();

    cout << ans.first << ' ' << ans.second << '\n';

    // cout << f(2911 - 1) << '\n';

    return 0;
}