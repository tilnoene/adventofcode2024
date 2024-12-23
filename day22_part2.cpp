#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAX = 2244;
const int GENERATED = 2000;

ll mix(ll a, ll b) {
    return a ^ b;
}

ll prune(ll x) {
    return x % 16777216;
}

ll next(ll secret) {
    secret = prune(mix(secret * 64, secret));
    secret = prune(mix(secret / 32, secret));
    secret = prune(mix(secret * 2048, secret));

    return secret;
}

int get_last_digit(ll x) {
    return to_string(x).back() - '0';
}

map<array<int, 4>, int> best;

int main() {
    for (int i = 0; i < MAX; i++) {
        ll x; cin >> x;
        vector<ll> values(GENERATED + 1);

        values[0] = x;
        
        for (int j = 1; j <= GENERATED; j++) {
            values[j] = next(values[j - 1]);
        }

        map<array<int, 4>, int> current;

        vector<int> diff(GENERATED + 1);

        for (int j = 1; j <= GENERATED; j++) {
            diff[j - 1] = get_last_digit(values[j]) - get_last_digit(values[j - 1]);

            if (j >= 4) {
                array<int, 4> aux = { diff[j - 4], diff[j - 3], diff[j - 2], diff[j - 1] };

                if (current.find(aux) == current.end()) {
                    current[aux] = get_last_digit(values[j]);
                }
            }
        }

        for (auto [key, val] : current) {
            best[key] += val;
        }
    }

    int ans = 0;

    for (auto [key, val] : best) {
        ans = max(ans, val);
    }

    cout << ans << '\n';

    return 0;
}