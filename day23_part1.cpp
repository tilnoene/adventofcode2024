#include <bits/stdc++.h>

using namespace std;

array<string, 3> conv(string u, string v, string w) {
    vector<string> arr = {u, v, w};
    sort(arr.begin(), arr.end());
    return { arr[0], arr[1], arr[2] };
}

int main() {
    int m = 3380;
    map<string, set<string>> adj;
    vector<pair<string, string>> edges;

    set<string> nodes;

    for (int i = 0; i < m; i++) {
        string u, v; cin >> u >> v;

        edges.push_back({ u, v });

        adj[u].insert(v);
        adj[v].insert(u);

        nodes.insert(u);
        nodes.insert(v);
    }
    
    set<array<string, 3>> pos;

    for (auto [u, v] : edges) {
        for (auto w : adj[v]) {
            if (w != u && w != v && adj[u].find(w) != adj[u].end()) {
                pos.insert(conv(u, v, w));
            }
        }

        for (auto w : adj[u]) {
            if (w != u && w != v && adj[v].find(w) != adj[v].end()) {
                pos.insert(conv(u, v, w));
            }
        }
    }

    int ans = 0;

    for (auto [u, v, w] : pos) {
        if (u[0] == 't' || v[0] == 't' || w[0] == 't') {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}