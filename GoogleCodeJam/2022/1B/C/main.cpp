#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int ones(int x)
{
    int res = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (x % 2 == 1)
            ++res;
        x /= 2;
    }
    return res;
}

int shift(int x, int v)
{
    int lower = (x >> v);
    int upper = (x << (8 - v));
    return (upper + lower) & 0xff;
}

int main()
{
    vector<int> mask;
    vector<int> used(256, 0);
    for (int i = 0; i < 255; ++i)
    {
        if (used[i] == 0)
        {
            mask.push_back(i);
        }
        used[i] = 1;
        for (int j = 0; j < 8; ++j)
        {
            int y = shift(i, j);
            used[y] = 1;
        }
    }

    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        std::vector<int> maybe;
        for (int i = 0; i < 256; ++i)
        {
            maybe.push_back(i);
        }
        cout << "00000000" << endl;
        int x;
        cin >> x;
        auto it = remove_if(maybe.begin(), maybe.end(), [x](int v) { return ones(v) != x;});
        maybe.erase(it, maybe.end());

        while (true)
        {
                int best = -1;
                set<int> best_vals[9];
                int best_mask = 0;
                for (int m : mask)
                {
                    set<int> vals[9];
                    for (int x : maybe)
                    {
                        for (int j = 0; j < 8; ++j)
                        {
                            int y = shift(m, j);
                            int z = (x ^ y);
                            vals[ones(z)].insert(z);
                        }
                    }
                    int v = 0;
                    for (int i = 0; i < 9; ++i)
                        v = max(static_cast<size_t>(v), vals[i].size());
                    if (best == -1 || v < best)
                    {
                        best = v;
                        for (int i = 0; i < 8; ++i)
                            best_vals[i] = move(vals[i]);
                        best_mask = m;
                    }
                }
                string s;
                for (int i = 0; i < 8; ++i)
                {
                    s += to_string(best_mask % 2);
                    best_mask /= 2;
                }
                cout << s << endl;
                cin >> x;
                if (x == 8)
                {
                    cout << "11111111" << endl;
                    cin >> x;
                }
                if (x == 0)
                {
                    break;
                }
                maybe = vector<int>(best_vals[x].begin(), best_vals[x].end());
        }
    }
    return 0;
}
