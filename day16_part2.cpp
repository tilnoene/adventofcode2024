#include <bits/stdc++.h>

using namespace std;

const int MAX = 256;
const long long INF = (long long)1e18;

int n, m;
char grid[MAX][MAX];

int di[] = {0, 1, 0, -1};
int dj[] = {1, 0, -1, 0};

vector<vector<vector<long long>>> dijkstra(int is, int js, int dirs) {
    vector<vector<vector<long long>>> d(MAX, vector<vector<long long>>(MAX, vector<long long>(4, INF)));

    set<tuple<int, int, int, int>> s; // { dist, i, j, dir }

    d[is][js][dirs] = 0;
    s.insert({ 0, is, js, dirs });

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

    return d;
}

long long dist(int d1, int d2) {
    int diff = abs(d1 - d2);

    if (diff == 3) {
        return 1;
    } else {
        return diff;
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

    auto ds = dijkstra(is, js, 0);
    vector<vector<vector<vector<long long>>>> de = { dijkstra(ie, je, 0), dijkstra(ie, je, 1), dijkstra(ie, je, 2), dijkstra(ie, je, 3) };
    
    long long mn = INF;

    for (int i = 0; i < 4; i++) {
        mn = min(mn, ds[ie][je][i]);
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool can = false;

            for (int di = 0; di < 4; di++) {
                for (int dj = 0; dj < 4; dj++) {
                    long long spent = 1;

                    if (di != dj) {
                        spent = dist(di, (dj + 2) % 4) * 1000;
                    }

                    for (int it = 0; it < 4; it++) {
                        if (ds[i][j][di] + spent + de[it][i][j][dj] == mn) {
                           can = true;
                        }
                    }
                }
            }

            if (can) {
                ans++;
                cout << 'O';
            } else {
                cout << grid[i][j];
            }
        }
        cout << '\n';
    }
    cout << '\n';

    cout << ans << '\n';

    return 0;
}