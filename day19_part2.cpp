#include <bits/stdc++.h>

using namespace std;

const int MAX = 4096;

int cnt_towels;
string towels[MAX];
long long memo[MAX];

// consigo colocar a toalha "towel" na sequencia "seq" partindo de i?
bool can(string& towel, string& seq, int i) {
    if (i + towel.size() - 1 >= seq.size()) {
        return false;
    }

    int it = 0;

    while (it < towel.size()) {
        if (seq[i] != towel[it]) {
            return false;
        }

        i++;
        it++;
    }

    return true;
}

long long dp(int i, string& seq) {

    if (i >= (int)seq.size()) {
        return 1;
    }

    if (memo[i] != -1) {
        return memo[i];
    }

    memo[i] = 0;

    // faço as transições
    for (int j = 0; j < cnt_towels; j++) {
        if (can(towels[j], seq, i)) {
            memo[i] += dp(i + towels[j].size(), seq);
        }
    }

    return memo[i];
}

int main() {
    cnt_towels = 446 + 1;

    for (int i = 0; i < cnt_towels; i++) {
        cin >> towels[i];
    }

    int cnt_seq = 402 - 3 + 1;
    long long ans = 0;

    for (int i = 0; i < cnt_seq; i++) {
        string seq; cin >> seq;

        memset(memo, -1, sizeof(memo));

        ans += dp(0, seq);
    }

    cout << ans << '\n';

    return 0;
}