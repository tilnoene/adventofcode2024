#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9 + 17;

char get_dir_i(int y) {
    if (y < 0) {
        return '^';
    } else if (y > 0) {
        return 'v';
    }

    return '=';
}

char get_dir_j(int x) {
    if (x < 0) {
        return '<';
    } else if (x > 0) {
        return '>';
    }

    return '=';
}

string create_sequence(int sz, char c) {
    string s = "";

    for (int i = 0; i < sz; i++) {
        s += c;
    }

    return s;
}

struct DirPad {
    int it, jt;
    vector<vector<char>> grid;
    vector<pair<int, int>> pos;

    DirPad() {
        it = 0;
        jt = 2;

        pos.assign(256, { INF, INF });
        grid.assign(2, vector<char>(4, ' '));

        {
            grid[0][1] = '^';
            grid[0][2] = 'A';

            grid[1][0] = '<';
            grid[1][1] = 'v';
            grid[1][2] = '>';
        }

        {
            pos['^'] = { 0, 1 };
            pos['A'] = { 0, 2 };
            
            pos['<'] = { 1, 0 };
            pos['v'] = { 1, 1 };
            pos['>'] = { 1, 2 };
        }
    }

    pair<int, int> dist(char to) {
        return { pos[to].first - it, pos[to].second - jt };
    }

    string generate_move_sequence(char to) {
        auto [itt, jtt] = dist(to);

        string moves = "";

        if (it == 0 && pos[to].first != 0) { // i first
            moves += create_sequence(abs(itt), get_dir_i(itt));
            moves += create_sequence(abs(jtt), get_dir_j(jtt));
        } else {
            moves += create_sequence(abs(jtt), get_dir_j(jtt));
            moves += create_sequence(abs(itt), get_dir_i(itt));
        }

        return moves;
    }

    void move(char to) {
        it = pos[to].first;
        jt = pos[to].second;
    }
};

struct NumPad {
    int it, jt;
    vector<vector<char>> grid;
    vector<pair<int, int>> pos;

    NumPad() {
        it = 3;
        jt = 2;

        pos.assign(256, { INF, INF });
        grid.assign(4, vector<char>(3, ' '));

        {
            grid[0][0] = '7';
            grid[0][1] = '8';
            grid[0][2] = '9';
            
            grid[1][0] = '4';
            grid[1][1] = '5';
            grid[1][2] = '6';
            
            grid[2][0] = '1';
            grid[2][1] = '2';
            grid[2][2] = '3';
            
            grid[3][1] = '0';
            grid[3][2] = 'A';
        }

        {
            pos['7'] = { 0, 0 };
            pos['8'] = { 0, 1 };
            pos['9'] = { 0, 2 };
            
            pos['4'] = { 1, 0 };
            pos['5'] = { 1, 1 };
            pos['6'] = { 1, 2 };

            pos['1'] = { 2, 0 };
            pos['2'] = { 2, 1 };
            pos['3'] = { 2, 2 };

            pos['0'] = { 3, 1 };
            pos['A'] = { 3, 2 };
        }
    }

    pair<int, int> dist(char to) {
        return { pos[to].first - it, pos[to].second - jt };
    }

    string generate_move_sequence(char to) {
        auto [itt, jtt] = dist(to);

        string moves = "";

        if (it == 3 && pos[to].first != 3) { // i first
            moves += create_sequence(abs(itt), get_dir_i(itt));
            moves += create_sequence(abs(jtt), get_dir_j(jtt));
        } else {
            moves += create_sequence(abs(jtt), get_dir_j(jtt));
            moves += create_sequence(abs(itt), get_dir_i(itt));
        }

        return moves;
    }
    
    void move(char to) {
        it = pos[to].first;
        jt = pos[to].second;
    }
};

int main() {
    long long total = 0;

    for (int i = 0; i < 5; i++) {
        NumPad numpad;
        DirPad dirpad1, dirpad2;

        string seq, ans = ""; cin >> seq;

        for (auto to : seq) {
            string moves_numpad = numpad.generate_move_sequence(to) + "A";
            numpad.move(to);

            for (auto move_numpad : moves_numpad) {
                string moves_dirpad1 = dirpad1.generate_move_sequence(move_numpad) + "A";
                dirpad1.move(move_numpad);

                for (auto move_dirpad1 : moves_dirpad1) {
                    string moves_dirpad2 = dirpad2.generate_move_sequence(move_dirpad1) + "A";
                    dirpad2.move(move_dirpad1);

                    ans += moves_dirpad2;
                }
            }
        }

        seq.pop_back();

        total += ans.size() * stoll(seq);
    }
    
    cout << total << '\n';

    return 0;
}