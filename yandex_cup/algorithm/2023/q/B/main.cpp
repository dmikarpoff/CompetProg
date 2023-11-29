#include <iostream>
#include <map>
#include <vector>

using namespace std;

map<int, vector<int>> pos;

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        int val;
        cin >> val;
        pos[val].push_back(i);
    }
    int res = n + 1;
    int from = n;
    int to = -1;
    for (auto i = pos.begin(); i != pos.end() && m > 0; ++i)
    {
        if (i->second.size() <= m)
        {
            m -= i->second.size();
            from = min(from, i->second.front());
            to = max(to, i->second.back());
            /*
            cout << "Consuming " << i->first << endl;
            cout << "From = " << from << "; To = " << to << endl;
            cout << "Remains " << m << endl;
            */
            continue;
        }
        const auto& v = i->second;
        // cout << "Choosing last " << m << endl;
        for (size_t j = 0; j + m <= v.size(); ++j)
        {
            auto f = min(from, v[j]);
            auto t = max(to, v[j + m - 1]);
            if (t - f + 1 < res)
            {
                res = t - f + 1;
            }
        }
        break;
    }
    if (m == 0)
    {
        cout << to - from + 1 << endl;
    }
    else
    {
        cout << res << endl;
    }
    return 0;
}
