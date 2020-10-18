#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_range(const std::vector<std::vector<int>>& s, int from, int to)
{
    int c = 0;
    for (int i = from; i <= to; ++i)
        c += s[i].size();
    cout << "? " << c << " ";
    for (int i = from; i <= to; ++i)
        for (auto v : s[i])
            cout << v << " ";
    cout << endl;
}

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> s(k);
        vector<int> a(k, -1);
        for (int i = 0; i < k; ++i)
        {
            int c;
            cin >> c;
            s[i].resize(c);
            for (auto& v : s[i])
                cin >> v;
        }
        int l = 0, r = k - 1;
        cout << "? " << n << " ";
        for (int i = 1; i <= n; ++i)
            cout << i << " ";
        cout << endl;
        int total_max;
        cin >> total_max;
        while (l < r)
        {
            int m = (l + r) / 2;
            print_range(s, l, m);
            int lower = 0;
            cin >> lower;
            if (total_max == lower)
            {
                r = m;
            }
            else
            {
                l = m + 1;
            }
        }

        int other = total_max;
        cout << "? " << n - s[r].size() << " ";
        for (int i = 1; i <= n; ++i)
            if (std::find(s[r].begin(), s[r].end(), i) == s[r].end())
                cout << i << " ";
        cout << endl;
        cin >> other;

        cout << "! ";
        for (int i = 0; i < k; ++i)
            cout << (i == r ? other : total_max) << " ";
        cout << endl;
        string decision;
        cin >> decision;
        if (decision == "Incorrect") {
            return 0;
        }
    }
    return 0;
}
