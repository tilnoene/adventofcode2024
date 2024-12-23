#include <bits/stdc++.h>

using pii = std::pair<int, int>;
using vii = std::vector<pii>;
using pci = std::pair<char, int>;
using move_sequence = std::array<pci, 3>;

const int NUMBER_OF_STRINGS_ON_INPUT = 5;
const int NUMBER_OF_DIRPADS = 25;

const long long INF = (long long)1e18 + 17;

pii dist(pii from, pii to) {
    return { to.first - from.first, to.second - from.second };
}

char get_dir_i(int dir) {
    if (dir < 0) {
        return '^';
    } else if (dir > 0) {
        return 'v';
    }

    return '=';
}

char get_dir_j(int dir) {
    if (dir < 0) {
        return '<';
    } else if (dir > 0) {
        return '>';
    }

    return '=';
}

void apply_movement(pii& cur, char dir) {
    assert(dir == '^' || dir == 'v' || dir == '<' || dir == '>');

    if (dir == '^') {
        cur.first -= 1;
    } else if (dir == 'v') {
        cur.first += 1;
    } else if (dir == '>') {
        cur.second += 1;
    } else if (dir == '<') {
        cur.second -= 1;
    }
}

namespace numpad {
    char grid[4][3] = {
        { '7', '8', '9' },
        { '4', '5', '6' },
        { '1', '2', '3' },
        { '$', '0', 'A' },
    };

    const pii NUMPAD_START_POSITION = { 3, 2 };
    pii pos[256];

    std::pair<move_sequence, move_sequence> generate_move_sequence(pii from, char to) {
        auto [di, dj] = dist(from, pos[to]);

        pci mi = { get_dir_i(di), abs(di) };
        pci mj = { get_dir_j(dj), abs(dj) };
        pci ma = { 'A', 1 };

        return {
            { mi, mj, ma },
            { mj, mi, ma },
        };
    }

    bool valid(pii cur, move_sequence seq) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < seq[i].second; j++) {
                apply_movement(cur, seq[i].first);

                if (grid[cur.first][cur.second] == '$') {
                    return false;
                }
            }
        }

        return true;
    }

    void move(pii& cur, char to) {
        cur = pos[to];
    }
}

namespace dirpad {
    char grid[2][3] = {
        { '$', '^', 'A' },
        { '<', 'v', '>' },
    };

    const pii DIRPAD_START_POSITION = { 0, 2 };
    pii pos[256];

    std::pair<move_sequence, move_sequence> generate_move_sequence(pii from, char to) {
        auto [di, dj] = dist(from, pos[to]);

        pci mi = { get_dir_i(di), abs(di) };
        pci mj = { get_dir_j(dj), abs(dj) };
        pci ma = { 'A', 1 };

        return {
            { mi, mj, ma },
            { mj, mi, ma },
        };
    }

    bool valid(pii cur, move_sequence seq) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < seq[i].second; j++) {
                apply_movement(cur, seq[i].first);

                if (grid[cur.first][cur.second] == '$') {
                    return false;
                }
            }
        }

        return true;
    }

    void move(pii& cur, char to) {
        cur = pos[to];
    }
}

void pre_process() {
    // dirpad

    dirpad::pos['^'] = { 0, 1 };
    dirpad::pos['A'] = { 0, 2 };
    
    dirpad::pos['<'] = { 1, 0 };
    dirpad::pos['v'] = { 1, 1 };
    dirpad::pos['>'] = { 1, 2 };

    // numpad

    numpad::pos['7'] = { 0, 0 };
    numpad::pos['8'] = { 0, 1 };
    numpad::pos['9'] = { 0, 2 };
    
    numpad::pos['4'] = { 1, 0 };
    numpad::pos['5'] = { 1, 1 };
    numpad::pos['6'] = { 1, 2 };

    numpad::pos['1'] = { 2, 0 };
    numpad::pos['2'] = { 2, 1 };
    numpad::pos['3'] = { 2, 2 };

    numpad::pos['0'] = { 3, 1 };
    numpad::pos['A'] = { 3, 2 };
}

std::map<std::pair<move_sequence, int>, long long> memo;

long long solve_dirpad(move_sequence seq, int current_dirpad, vii dirpads) {
    if (current_dirpad >= (int)dirpads.size()) {
        return seq[0].second + seq[1].second + seq[2].second;
    }

    std::pair<move_sequence, int> hash = { seq, current_dirpad };

    if (memo.find(hash) != memo.end()) {
        return memo[hash];
    }

    long long ans = 0;

    for (int d = 0; d < 3; d++) {
        if (seq[d].second == 0) {
            continue;
        }

        char to = seq[d].first;

        auto [sequence1, sequence2] = dirpad::generate_move_sequence(dirpads[current_dirpad], to);

        bool v1 = dirpad::valid(dirpads[current_dirpad], sequence1);
        bool v2 = dirpad::valid(dirpads[current_dirpad], sequence2);

        long long c1 = solve_dirpad(sequence1, current_dirpad + 1, dirpads) + (seq[d].second - 1);
        long long c2 = solve_dirpad(sequence2, current_dirpad + 1, dirpads) + (seq[d].second - 1);

        if (v1 && v2) {
            ans += std::min(c1, c2);
        } else if (v1) {
            ans += c1;
        } else {
            ans += c2;
        }

        dirpad::move(dirpads[current_dirpad], to);
    }

    return memo[hash] = ans;
}

long long solve_numpad(std::string seq) {
    pii np = numpad::NUMPAD_START_POSITION;
    vii dirpads(NUMBER_OF_DIRPADS, dirpad::DIRPAD_START_POSITION);

    long long ans = 0LL;

    for (char to : seq) {
        auto [sequence1, sequence2] = numpad::generate_move_sequence(np, to);

        bool v1 = numpad::valid(np, sequence1);
        bool v2 = numpad::valid(np, sequence2);

        long long c1 = solve_dirpad(sequence1, 0, dirpads);
        long long c2 = solve_dirpad(sequence2, 0, dirpads);

        if (v1 && v2) {
            ans += std::min(c1, c2);
        } else if (v1) {
            ans += c1;
        } else {
            ans += c2;
        }

        numpad::move(np, to);
    }

    return ans;
}

int main() {
    pre_process();

    long long total = 0;

    for (int i = 0; i < NUMBER_OF_STRINGS_ON_INPUT; i++) {
        std::string seq; std::cin >> seq;
        long long moves = solve_numpad(seq);

        seq.pop_back();

        total += moves * stoll(seq);
    }

    std::cout << total << '\n';

    return 0;
}