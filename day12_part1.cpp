#include <bits/stdc++.h>

using namespace std;

const int MAX = 140;

int n, m;
char grid[MAX][MAX];
bool visited[MAX][MAX];

long long area, perimeter;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int i, int j) {
    visited[i][j] = true;
    area += 1;
    perimeter += 4;

    for (int d = 0; d < 4; d++) {
        int it = i + dx[d];
        int jt = j + dy[d];

        if (it >= 0 && it < n && jt >= 0 && jt < m) {
            if (grid[it][jt] == grid[i][j]) {
                perimeter--;

                if (!visited[it][jt]) {
                    dfs(it, jt);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    n = m = 10;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    long long total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                area = 0;
                perimeter = 0;
                
                dfs(i, j);

                total += area * perimeter;
            }
        }
    }

    cout << total << '\n';

    return 0;
}