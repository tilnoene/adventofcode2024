#include <bits/stdc++.h>

using namespace std;

const int MAX = 2024;

int n, m;
char grid[MAX][MAX + MAX], newgrid[MAX][MAX + MAX];
bool visited[MAX][MAX + MAX];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int get_dir(char c) {
    if (c == '^') {
        return 3;
    } else if (c == 'v') {
        return 2;
    } else if (c == '<') {
        return 1;
    } else {
        return 0;
    }
}

void debug() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

bool bfs(int is, int js, int dir, vector<tuple<int, int, char>>& pieces) {
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            newgrid[i][j] = grid[i][j];
        }
    }

    bool can = true;

    queue<pair<int, int>> q; // "[" de cada peça

    q.push({ is, js });
    visited[is][js] = true;
    
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        pieces.push_back({ i, j, grid[i][j] });
        pieces.push_back({ i, j + 1, grid[i][j + 1] });

        int it = i + dx[dir];
        int jt = j + dy[dir];

        if (visited[it][jt]) {
            continue;
        }

        if (dir <= 1) { // > (0) or < (1)
            jt += dy[dir];

            if (dir == 0 && grid[it][jt] == '#') {
                return false;
            } else if (dir == 1 && grid[it][jt + 1] == '#') {
                return false;
            } else if (grid[it][jt] == '[') {
                // (i, j) -> (it, jt) -> (itt, jtt)

                q.push({ it, jt });
                visited[it][jt] = true;
            }
        } else { // v (2) or ^ (3)
            // eu sou um [
            
            if (grid[it][jt] == '#' || grid[it][jt + 1] == '#') {
                return false;
            } else if (grid[it][jt] == '[') { // um [] alinhado em cima de mim
                q.push({ it, jt });
                visited[it][jt] = true;
            } else {

                // [][] [].. ..[]
                // .[]. .[]. .[].

                if (grid[it][jt] == ']') {
                    q.push({ it, jt - 1 });
                    visited[it][jt - 1] = true;
                }

                if (grid[it][jt + 1] == '[') {
                    q.push({ it, jt + 1 });
                    visited[it][jt + 1] = true;
                }
            }

        }
    }

    return can;
}

int main() {
    n = m = 50;

    int it, jt;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;

            if (c == '#') {
                grid[i][2 * j] = '#';
                grid[i][2 * j + 1] = '#';
            } else if (c == '.') {
                grid[i][2 * j] = '.';
                grid[i][2 * j + 1] = '.';
            } else if (c == '@') {
                grid[i][2 * j] = '@';
                grid[i][2 * j + 1] = '.';

                it = i;
                jt = 2 * j;
            } else {
                grid[i][2 * j] = '[';
                grid[i][2 * j + 1] = ']';
            }
        }
    }

    m += m;

    string moves = "";

    for (int i = 0; i < 71 - 52 + 1; i++) {
        string s; cin >> s;
        moves += s;
    }

    //debug();

    for (auto move : moves) {
        int dir = get_dir(move);

        vector<tuple<int, int, char>> pieces;
        pieces.push_back({ it, jt, '@' });

        int i = it + dx[dir];
        int j = jt + dy[dir];

        if (grid[i][j] != '#') {
            bool can = true;

            if (grid[i][j] == '[') {
                can = bfs(i, j, dir, pieces);
            } else if (grid[i][j] == ']') {
                can = bfs(i, j - 1, dir, pieces);
            }

            if (can) {
                for (auto [i, j, _] : pieces) {
                    grid[i][j] = '.';
                }

                for (auto [i, j, c] : pieces) {
                    grid[i + dx[dir]][j + dy[dir]] = c;
                }

                it = i;
                jt = j;
            }
        }

        //debug();
    }

    long long answer = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '[') {
                answer += i * 100 + j;
            }
        }
    }

    cout << answer << '\n';
    
    return 0;
}