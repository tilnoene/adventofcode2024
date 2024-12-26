#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAX = 333;
const int INF = 1e9 + 17;

ll x, y;
vector<int> val_original(MAX, -1);
string volta[MAX];
vector<int> adj[MAX];

int it = 1;
map<string, int> id;

int get_id(string s) {
    if (id.find(s) == id.end()) {
        id[s] = it;
        volta[it] = s;
        it++;
    }

    return id[s];
}

vector<tuple<int, string, int>> operations;
vector<int> results;

string lpad(int x) {
    string s = "";

    if (x < 10) {
        s += "0";
    }

    return s + to_string(x);
}

ll get(char c, vector<int>& val) {
    string s = "";
    int it = 0;

    while (true) {
        string aux = "";
        aux += c;
        aux += lpad(it);

        if (id.find(aux) == id.end()) {
            break;
        }

        if (val[get_id(aux)] == -1) {
            return -1;
        }

        s += val[get_id(aux)] + '0';
        it++;
    }

    reverse(s.begin(), s.end());

    return bitset<50>(s).to_ullong();
}

int dist(ll a, ll b) {
    int ans = 0;

    for (int i = 0; i < 50; i++) {
        ll pot = (1LL << i);

        if ((pot&a) != (pot&b)) {
            ans++;
        }
    }

    return ans;
}

int solve() {
    vector<int> val(val_original);

    auto calc = [&](int v1, string op, int v2) -> int {
        if (op == "AND") {
            return v1 & v2;
        } else if (op == "OR") {
            return v1 | v2;
        } else {
            return v1 ^ v2;
        }
    };

    while (true) {
        bool flag = false;

        for (int i = 0; i < results.size(); i++) {
            auto [v1, op, v2] = operations[i];
            auto result = results[i];

            if (val[v1] != -1 && val[v2] != -1 && val[result] == -1) {
                val[result] = calc(val[v1], op, val[v2]);
                flag = true;
            }
        }

        if (!flag) {
            break;
        }
    }

    ll z = get('z', val);

    if (z == -1) {
        return INF;
    }

    return dist(z, x + y);
}

string get_name(char c, int it) {
    string ans = "";
    ans += c;
    ans += lpad(it);
    return ans;
}

void apply_original(char c, ll x) {
    // val_original.assign(MAX, -1);

    for (int i = 0; i < 45; i++) {
        ll pot = (1LL << i);

        if (pot&x) {
            val_original[get_id(get_name(c, i))] = 1;
        } else {
            val_original[get_id(get_name(c, i))] = 0;
        }
    }
}

// 100 random numbers of 45 bits each
vector<ll> numbers = { 25491299606221, 27561610995737, 21423100322611, 30202091139845, 30410691490492, 28635558758671, 19727492155606, 18358471290564, 33630921230834, 21155915022903, 18244572801791, 22083844493593, 20096930595347, 31574745212523, 21682726942682, 18703397356978, 34557037227030, 28420286932986, 33496233090858, 31238364534476, 33549394954623, 29963759121950, 31898001596501, 18307144679865, 33307762714122, 34745191368915, 34944435361414, 18206048759608, 20253972635182, 25206844663377, 17688128422147, 23743696156581, 26880994531919, 24500251511225, 32384311735823, 28028820150200, 34413626112119, 30931854290698, 23265198962694, 23269100865086, 21428447530203, 21012885630220, 26694914373583, 22026482344352, 29741955909514, 33367275913154, 23289749820723, 21608149859706, 34624990828630, 23968507901703, 30256949418918, 34714447245222, 22311529604358, 28140857050550, 24176083840053, 24427810424800, 32606321171036, 21747421923607, 32121874763765, 22898114613926, 33252242568146, 23748406280713, 23746270718125, 30880709483987, 27577982776543, 23849108519410, 31314437390732, 29683218535617, 17697016822618, 17780846733686, 35163587208064, 33159542540715, 28512946738971, 28012735105118, 33773046720790, 28484388739365, 33005922912291, 26536664073693, 31346178743621, 35137044100968, 18253464227406, 30089252532626, 19122201465989, 18142794587889, 28784073042652, 30068921983719, 23168803782580, 33404467302772, 30517636378731, 25663808793966, 20721011316163, 32947300797391, 21291252560699, 21858866774948, 26978630644406, 30559010840719, 26728094365229, 32782760372352, 34389970573282, 23617122377080 };

// ordena pelo menor score
int get_score() {
    int mx = 0;

    for (int k = 0; k < 50; k += 2) {
        x = numbers[k];
        apply_original('x', numbers[k]);
        
        y = numbers[k + 1];
        apply_original('y', numbers[k + 1]);

        mx = max(mx, solve());
    }

    return mx;
}

void brute(vector<pair<int, int>> changes, int score) {
    if (changes.size() >= 4) {
        if (score != 0) {
            return;
        }

        cout << score << '\n';

        for (auto [ff, ss] : changes) {
            cout << volta[results[ff]] << ' ' << volta[results[ss]] << '\n';
        }
        cout << '\n';
        
        cout.flush();

        return;
    }

    vector<array<int, 3>> possibilities; // { score, id1, id2 }

    for (int i = 0; i < (int)results.size(); i++) {
        for (int j = i + 1; j < (int)results.size(); j++) {
            bool used = false;

            for (auto [it, jt] : changes) {
                if (it == i || it == j || jt == j || jt == j) {
                    used = true;
                    break;
                }
            }

            if (!used) {
                swap(results[i], results[j]);

                auto score = get_score();

                if (score < INF) {
                    possibilities.push_back({ score, i, j });
                }

                swap(results[i], results[j]);
            }
        }
    }

    sort(possibilities.begin(), possibilities.end()); // ordena pelo menor score

    for (auto [score, i, j] : possibilities) {
        swap(results[i], results[j]);

        auto aux(changes);
        aux.push_back({ i, j });
        brute(aux, score);

        swap(results[i], results[j]);
    }
}

int main() {
    for (int i = 0; i < 90; i++) {
        string node; cin >> node;
        node.pop_back(); // remove the ":"

        int v; cin >> v;
        val_original[get_id(node)] = v;
    }

    // x = get('x', val_original);
    // y = get('y', val_original);

    for (int i = 0; i < 313 - 92 + 1; i++) {
        string a, op, b, _, result;
        cin >> a >> op >> b >> _ >> result;

        operations.push_back(make_tuple(get_id(a), op, get_id(b)));
        results.push_back(get_id(result));
    }

    // cout << get_score() << '\n';
    
    brute({}, 1e9 + 17);

    return 0;
}