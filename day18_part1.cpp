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

int main() {
    clear_grid();

    for (int i = 0; i < 1024; i++) {
        int it, jt; cin >> it >> jt;
        grid[jt][it] = '#';
    }

    bfs(0, 0);

    cout << dist[n - 1][n - 1] << '\n';

    return 0;
}