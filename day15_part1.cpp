#include <bits/stdc++.h>

using namespace std;

const int MAX = 2024;

int n, m;
char grid[MAX][MAX];

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

int main() {
    n = 50;
    m = 50;

    int it, jt;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == '@') {
                it = i;
                jt = j;
            }
        }
    }

    string moves = "";

    for (int i = 0; i < 71 - 52 + 1; i++) {
        string s; cin >> s;
        moves += s;
    } 

    for (auto move : moves) {
        int dir = get_dir(move);

        int i = it, j = jt;

        do {
            i += dx[dir];
            j += dy[dir];
        } while (grid[i][j] == 'O');

        if (grid[i][j] == '.') {
            grid[i][j] = 'O';

            grid[it][jt] = '.';
            it += dx[dir];
            jt += dy[dir];
            grid[it][jt] = '@';
        }
    }

    long long answer = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'O') {
                answer += i * 100 + j;
            }

            // cout << grid[i][j];
        }
        // cout << '\n';
    }

    cout << answer << '\n';
    
    return 0;
}