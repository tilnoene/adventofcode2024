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

const int MAX = 64;

char grid[MAX][MAX];

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool colinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    return x1 * y2 + y1 * x3 + x2 * y3 - y2 * x3 - y3 * x1 - x2 * y1 == 0;
}

void solve() {
    int n = 50;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // tenta colocar uma # aqui (antinode)]

            for (int i1 = 0; i1 < n; i1++) {
                for (int j1 = 0; j1 < n; j1++) {
                    for (int i2 = 0; i2 < n; i2++) {
                        for (int j2 = 0; j2 < n; j2++) {
                            if (i1 == i2 && j1 == j2) {
                                continue;
                            }
                            
                            if (grid[i1][j1] == grid[i2][j2] && grid[i1][j1] != '.' && colinear(i, j, i1, j1, i2, j2)) {

                                if (dist(i, j, i1, j1) == 2 * dist(i, j, i2, j2) || 2 * dist(i, j, i1, j1) == dist(i, j, i2, j2)) {
                                    ans++;
                                    goto end;
                                }

                            }

                        }
                    }
                }
            }

            end:;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}