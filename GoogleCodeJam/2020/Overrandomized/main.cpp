#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int u;
        cin >> u;
        map<char, int> p;
        for (int i = 0; i < 10000; ++i)
        {
            int q;
            char s[20] = {0};
            scanf("%d%s", &q, s);
            auto l = strlen(s);
            for (size_t j = 0; j < l; ++j)
            {
                if (j == 0)
                {
                    p[s[j]]++;
                }
                p[s[j]];
            }
        }
        /*
        for (size_t i = 0; i < 1; ++i)
        {
            cout << i << ": " << endl;
            for (auto m : p[i])
                cout << '{' << m.first << ": " << m.second << "}, ";
            cout << endl;
        }
        */
        vector<pair<int, char>> order;
        for (auto m : p)
            order.emplace_back(m.second, m.first);
        sort(order.begin(), order.end());
        cout << "Case #" << o + 1 << ": ";
        cout << order[0].second;
        for (int i = 9; i >= 1; --i)
            cout << order[i].second;
        cout << endl;
    }
    return 0;
}
