#include <iostream>
#include <map>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 1; o <= t; ++o)
    {
        int n, a, b;
        cin >> n >> a >> b;
        map<int, int> req;
        for (int i = 1; i <= n; ++i)
        {
            int u;
            cin >> u;
            if (u > 0)
            {
                req[i] = u;
            }
        }
        int found = -1;
        for (int i = n + 1; i <= 1500 && found == -1; ++i)
        {
            // cout << "i = " << i << endl;
            auto r = req;
            map<int, int> cur;
            cur[i] = 1;
            while (!cur.empty())
            {
                auto k = cur.rbegin()->first;
                auto x = cur.rbegin()->second;
                cur.erase(k);
                if (k - a > 0)
                {
                    cur[k - a] += x;
                    cur[k - a] = min(cur[k - a], 1000);
                }
                if (k - b > 0)
                {
                    cur[k - b] += x;
                    cur[k - b] = min(cur[k - b], 1000);
                }
                for (auto& p : r)
                {
                    auto it = cur.find(p.first);
                    if (it != cur.end())
                    {
                        int d = min(p.second, it->second);
                        it->second -= d;
                        p.second -= d;
                    }
                }
                for (auto j = r.begin(); j != r.end();)
                {
                    if (j->second == 0)
                    {
                        j = r.erase(j);
                    }
                    else
                    {
                        ++j;
                    }
                }
                if (r.empty())
                {
                    found = i;
                    break;
                }
                for (auto j = cur.begin(); j != cur.end();)
                {
                    if (j->second == 0)
                    {
                        j = cur.erase(j);
                    }
                    else
                    {
                        ++j;
                    }
                }
            }
        }
        cout << "Case #" << o << ": ";
        cout << (found == -1 ? "IMPOSSIBLE" : std::to_string(found));
        cout << endl;
    }
    return 0;
}
