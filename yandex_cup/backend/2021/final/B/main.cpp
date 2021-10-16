#include <iostream>
#include <vector>
#include <set>
#include <cassert>

#include "json.hpp"

using namespace std;

template <class U, class V>
void merge(U& lhs, const V& rhs, const set<string>& special)
{
    for (const auto& el: rhs.items())
    {
        if (lhs.find(el.key()) == lhs.end() || special.find(el.key()) != special.end())
        {
            if (lhs.find(el.key()) == lhs.end())
            {
                lhs.erase(el.key());
            }
            lhs[el.key()] = el.value();
            continue;
        }
        merge(lhs[el.key()], el.value(), special);
    }
}

int main()
{
    int n;
    cin >> n;
    nlohmann::json js({});
    string tmp;
    getline(cin, tmp);
    for (int i = 0; i < n; ++i)
    {
        string cmd;
        getline(cin, cmd);
        if (cmd == "MERGE")
        {
            int k;
            cin >> k;
            set<string> special;
            for (int j = 0; j < k; ++j)
            {
                string s;
                cin >> s;
                special.insert(s);
            }
            int t;
            cin >> t;
            getline(cin, tmp);
            string other;
            for (int j = 0; j < t; ++j)
            {
                string s;
                getline(cin, s);
                other += s;
            }
            const auto other_json = nlohmann::json::parse(other);
            merge(js, other_json, special);
        }
        else if (cmd == "PRINT")
        {
            cout << js.dump() << endl;
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}
