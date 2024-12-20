#include <bits/stdc++.h>

using namespace std;

const int MAX = 333;
const int INF = (int)1e9 + 17;

int n;
char grid[MAX][MAX];

int di[] = {0, 0, 1, -1};
int dj[] = {1, -1, 0, 0};

vector<vector<int>> dijkstra(int is, int js) {
    vector<vector<int>> dist(n, vector<int>(n, INF));

    set<tuple<int, int, int>> s; // { dist, i, j }

    s.insert({ 0, is, js });
    dist[is][js] = 0;

    while (!s.empty()) {
        auto [d, i, j] = *s.begin();
        s.erase(s.begin());

        for (int k = 0; k < 4; k++) {
            int it = i + di[k];
            int jt = j + dj[k];

            if (it >= 0 && it < n && jt >= 0 && jt < n && grid[it][jt] != '#') {

                if (dist[it][jt] > dist[i][j] + 1) {
                    s.erase({ dist[it][jt], it, jt });
                    
                    dist[it][jt] = dist[i][j] + 1;
                    
                    s.insert({ dist[it][jt], it, jt });
                }

            }
        }
    }

    return dist;
}

int main() {
    n = 141;

    int is, js, ie, je;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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

    auto ds = dijkstra(is, js);
    auto de = dijkstra(ie, je);

    int mn = ds[ie][je], ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            for (int it = max(0, i - 20); it <= min(i + 20, n - 1); it++) {
                for (int jt = max(0, j - 20); jt <= min(j + 20, n - 1); jt++) {
                    int cur_dist = abs(it - i) + abs(jt - j);

                    if (cur_dist <= 20 && grid[it][jt] != '#') {

                        int aux_dist = ds[i][j] + cur_dist + de[it][jt];
                        int saved = mn - aux_dist;

                        if (saved >= 100) {
                            ans++;
                        }

                    }

                }
            }

        }
    }

    cout << ans << '\n';

    return 0;
}