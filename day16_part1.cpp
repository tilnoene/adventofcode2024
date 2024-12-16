#include <bits/stdc++.h>

using namespace std;

const int MAX = 2024;
const long long INF = (long long)1e18;

int n, m;
char grid[MAX][MAX];
long long d[MAX][MAX][4];

int di[] = {0, 1, 0, -1};
int dj[] = {1, 0, -1, 0};

void dijkstra(int is, int js) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            d[i][j][0] = INF;
            d[i][j][1] = INF;
            d[i][j][2] = INF;
            d[i][j][3] = INF;
        }
    }

    set<tuple<int, int, int, int>> s; // { dist, i, j, dir }

    d[is][js][0] = 0;
    s.insert({ 0, is, js, 0 });

    while (!s.empty()) {
        auto [dist, i, j, dir] = *s.begin();
        s.erase(s.begin());

        {
            int it = i + di[dir];
            int jt = j + dj[dir];

            if (it >= 0 && it < n && jt >= 0 && jt < m && grid[it][jt] != '#') {
                if (d[i][j][dir] + 1 < d[it][jt][dir]) {
                    s.erase({ d[it][jt][dir], it, jt, dir });

                    d[it][jt][dir] = d[i][j][dir] + 1;
                    
                    s.insert({ d[it][jt][dir], it, jt, dir });
                }
            }
        }
        
        {
            int dir1 = (dir + 1) % 4;

            if (d[i][j][dir] + 1000 < d[i][j][dir1]) {
                s.erase({ d[i][j][dir1], i, j, dir1 });
                
                d[i][j][dir1] = d[i][j][dir] + 1000;

                s.insert({ d[i][j][dir1], i, j, dir1 });
            }
        }

        {
            int dir1 = (dir - 1 + 4) % 4;

            if (d[i][j][dir] + 1000 < d[i][j][dir1]) {
                s.erase({ d[i][j][dir1], i, j, dir1 });
                
                d[i][j][dir1] = d[i][j][dir] + 1000;

                s.insert({ d[i][j][dir1], i, j, dir1 });
            }
        }
    }
}

int main() {
    n = 141;
    m = 141;

    int is, js, ie, je;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'S') {
                is = i;
                js = j;
            } else if (grid[i][j] == 'E') {
                ie = i;
                je = j;
            }
        }
    }

    dijkstra(is, js);

    long long ans = INF;

    for (int i = 0; i < 4; i++) {
        ans = min(ans, d[ie][je][i]);
    }

    cout << ans << '\n';

    return 0;
}