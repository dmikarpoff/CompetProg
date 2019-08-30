#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

vector<int> duons(8, 0);
const vector<string> simple_edge = {
    "BDE","ACF", "BDG", "ACH", "AFH", "BEG", "CFH", "DEG"
};
const map<char, char> opposite_edge = {
    {'A', 'G'}, {'B', 'H'}, {'C', 'E'}, {'D', 'F'},
    {'F', 'D'}, {'E', 'C'}, {'H', 'B'}, {'G', 'A'}
};

int main()
{
    for (char c = 'A'; c <= 'H'; ++c)
    {
        cin >> duons[c - 'A'];
    }
    vector<string> res;
    for (size_t i = 0; i < duons.size(); ++i)
    {
        for (char c : simple_edge[i])
        {
            auto cnt = min(duons[i], duons[c - 'A']);
            if (cnt > 0)
            {
                duons[i] -= cnt;
                duons[c - 'A'] -= cnt;
                string line = string("") + static_cast<char>(i + 'A') + c + '-';
                res.resize(res.size() + cnt, line);
            }
        }
    }
    for (char c = 'A'; c <= 'D'; ++c)
    {
        char opposite = opposite_edge.find(c)->second;
        if (duons[c - 'A'] != duons[opposite - 'A'])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        char down = (c - 'A' + 1) % 4 + 'A';
        char up = (opposite - 'E' + 3) % 4 + 'E';
        char str[10];
        sprintf(str, "%c%c+", up, down);
        res.resize(res.size() + duons[c - 'A'], str);
        sprintf(str, "%c%c-", c, down);
        res.resize(res.size() + duons[c - 'A'], str);
        sprintf(str, "%c%c-", opposite, up);
        res.resize(res.size() + duons[c - 'A'], str);
    }
    /*
    if (any_of(duons.begin(), duons.end(), [](auto v) {return v != 0;}))
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    */
    for (auto s : res)
        cout << s << "\n";
    cout << endl;
    return 0;
}
