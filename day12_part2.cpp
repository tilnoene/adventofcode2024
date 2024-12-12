#include <bits/stdc++.h>

using namespace std;

const int MAX = 256;

int n, m;
char grid[MAX][MAX], aux[MAX][MAX];
bool visited[MAX][MAX];

long long area, perimeter;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int i, int j) {
    visited[i][j] = true;
    area += 1;
    perimeter += 4;

    aux[i][j] = grid[i][j];

    for (int d = 0; d < 4; d++) {
        int it = i + dx[d];
        int jt = j + dy[d];

        if (it >= 1 && it <= n && jt >= 1 && jt <= m) {
            if (grid[it][jt] == grid[i][j]) {
                perimeter--;

                if (!visited[it][jt]) {
                    dfs(it, jt);
                }
            }
        }
    }
}

void reset_aux() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            aux[i][j] = '.';
        }
    }
}

void print_aux() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << aux[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

long long get_sides() {
    long long ans = 0;

    for (int j = 0; j < MAX - 1; j++) {
        int consec = 0;

        for (int i = 0; i < MAX; i++) {
            if (aux[i][j] == '.' && aux[i][j + 1] != '.') {
                consec++;
            } else {
                consec = 0;
            }

            if (consec == 1) {
                ans++;
            }
        }
    }

    for (int j = 1; j < MAX; j++) {
        int consec = 0;

        for (int i = 0; i < MAX; i++) {
            if (aux[i][j] == '.' && aux[i][j - 1] != '.') {
                consec++;
            } else {
                consec = 0;
            }

            if (consec == 1) {
                ans++;
            }
        }
    }

    for (int i = 0; i < MAX - 1; i++) {
        int consec = 0;

        for (int j = 0; j < MAX; j++) {
            if (aux[i][j] == '.' && aux[i + 1][j] != '.') {
                consec++;
            } else {
                consec = 0;
            }

            if (consec == 1) {
                ans++;
            }
        }
    }
    
    for (int i = 1; i < MAX; i++) {
        int consec = 0;

        for (int j = 0; j < MAX; j++) {
            if (aux[i][j] == '.' && aux[i - 1][j] != '.') {
                consec++;
            } else {
                consec = 0;
            }

            if (consec == 1) {
                ans++;
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    n = m = 140;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }

    long long total = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!visited[i][j]) {
                area = 0;
                perimeter = 0;
                reset_aux();

                dfs(i, j);

                long long sides = get_sides();
            
                total += area * sides;
            }
        }
    }

    cout << total << '\n';

    return 0;
}