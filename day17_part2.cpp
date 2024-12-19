#include <bits/stdc++.h>
#define int long long

using namespace std;
using ll = long long;

vector<int> execute(int a) {
    int b, c;
    vector<int> aux;

    while (a != 0) {
        b = a % 8;
        b = b ^ 2;
        c = a / pow(2, b);
        b = b ^ c;
        b = b ^ 3;
        aux.push_back(b % 8);
        a = a / 8;
    }

    return aux;
}

void debug(vector<int> arr) {
    for (auto e : arr) {
        cout << e << ' ';
    }
    cout << '\n';
}

bool is_suff(vector<int> a, vector<int> b) {
    int it = a.size() - 1;
    int jt = b.size() - 1;

    while (it >= 0 && jt >= 0) {
        if (a[it] != b[jt]) {
            return false;
        }

        it--, jt--;
    }

    return true;
}

void brute(int x, vector<int> arr, vector<int>& program) {
    auto out = execute(x);

    if (out == program) {
        cout << x << '\n';
        exit(0);
    }

    x *= 8;
    for (int i = 0; i < 8; i++) {
        out = execute(x + i);

        if (is_suff(out, program)) {
            auto copy = arr;
            copy.push_back(x + i);
            brute(x + i, copy, program);
        }
    }
}

signed main() {
    int n; cin >> n;
    vector<int> program(n);

    for (int i = 0; i < n; i++) {
        cin >> program[i];
    }

    brute(1, {}, program);

    auto out = execute(37221270076916);

    debug(out);

    return 0;
}