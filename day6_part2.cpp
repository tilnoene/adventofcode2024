#include <bits/stdc++.h>

#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair

// n acho que eu seja bom, mas eu ja fui pior

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vii = vector<pii>;
using vll = vector<pll>;
using tii = tuple<int, int, int>;
using tll = tuple<ll, ll, ll>;
using ld = long double;

template<class T, class U> auto &operator>>(istream &is, pair<T, U> &p) { return is >> p.ff >> p.ss; }
template<class T, class U> auto &operator<<(ostream &os, pair<T, U> const& p) { return os << '(' << p.first << ' ' << p.second << ')'; }

const auto ES = "", SEP = " ";
template<class T> auto &operator>>(istream& is, vector<T> &c) { for (auto &x : c) is >> x; return is; }
template<class T> auto &operator<<(ostream& os, vector<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class T> auto &operator<<(ostream& os, set<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class T> auto &operator<<(ostream& os, multiset<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class T> auto &operator<<(ostream& os, deque<T> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class K, class V> auto &operator<<(ostream& os, map<K,V> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }
template<class K, class V> auto &operator<<(ostream& os, unordered_map<K,V> const &c) { auto sep = ES; for (auto x : c) os << sep << x, sep = SEP; return os; }

template<class... A> void in(A &...a) { ((cin >> a), ...); }
template<class... A> void out(A const&... a) { auto sep = ES; ((cout << sep << a, sep = SEP), ...); cout << '\n'; }
#define dbg(x) out("[", #x, "=", x, "] ")
#define debug(x) dbg(x)

// const int INF = (int)1e9 + 17;
// const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;
// const int MOD = (int)1e9 + 7;
// const int MOD = 998'244'353; // 119 * 2^23 + 1
// const ld EPS = 1e-8;
// const ld PI = acos(-1);

const int MAX = 200;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int n = 130;
int m = 130;
char grid[MAX][MAX];

bool loop;
bool visited[MAX][MAX][4];

void dfs(int i, int j, int dir) {
    visited[i][j][dir] = true;

    int it = i + dx[dir];
    int jt = j + dy[dir];
    
    if (it < 0 || it >= n || jt < 0 || jt >= m) {
        return;
    }

    if (grid[it][jt] == '#') {
        int newdir = (dir + 1) % 4;

        if (!visited[i][j][newdir]) {
            dfs(i, j, newdir);
        } else {
            loop = true;
        }
    } else {
        if (!visited[it][jt][dir]) {
            dfs(it, jt, dir);
        } else {
            loop = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int it, jt;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == '^') {
                it = i;
                jt = j;
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                grid[i][j] = '#';

                loop = false;
                memset(visited, 0, sizeof(visited));
                dfs(it, jt, 0);

                if (loop) {
                    ans += 1;
                }

                grid[i][j] = '.';
            }
        }
    }

    cout << ans << '\n';
    
    return 0;
}