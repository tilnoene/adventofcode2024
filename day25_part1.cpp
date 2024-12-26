#include <bits/stdc++.h>

using namespace std;

bool fit(array<int, 5> key, array<int, 5> lock) {
    for (int i = 0; i < 5; i++) {
        int mx = 5 - lock[i];

        if (key[i] > mx) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<array<int, 5>> locks, keys; 

    string s;
    while (cin >> s) {
        vector<vector<char>> grid(7, vector<char>(5, '.'));

        for (int i = 0; i < s.size(); i++) {
            grid[0][i] = s[i];
        }

        for (int i = 1; i < 7; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> grid[i][j];
            }
        }

        array<int, 5> current = { 0, 0, 0, 0, 0 };

        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < 7; i++) {
                current[j] += (grid[i][j] == '#');
            }

            current[j]--;
        }

        if (grid[0][0] == '#') {
            locks.push_back(current);
        } else {
            keys.push_back(current);
        }
    }

    int ans = 0;

    for (auto lock : locks) {
        for (auto key : keys) {
            if (fit(key, lock)) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}