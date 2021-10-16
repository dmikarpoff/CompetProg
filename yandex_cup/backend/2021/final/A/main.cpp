#include <iostream>
#include <set>
#include <cstdio>

using namespace std;

int main()
{
    set<int> free;
    for (int x = 100; x < 200; x += 5)
    {
        free.insert(x);
    }
    int n, t;
    cin >> n >> t;
    for (int i = 0; i < n; ++i)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            char c;
            int hl, ml, hu, mu;
            scanf("%d%c%d%c%d%c%d", &hl, &c, &ml, &c, &hu, &c, &mu);
            // cout << hl << " " << ml << " " << hu << " " << mu << endl;
            int f = hl * 10 + ml / 6;
            int u = hu * 10 + mu / 6;
            for (int j = f; j < u; j += 5)
            {
                free.erase(j);
            }
        }
    }
    int slots = t / 30;
    bool some_output = false;
    for (int i = 100; i < 200; i += 5)
    {
        bool ok = true;
        for (int j = 0; j < slots; ++j)
        {
            if (free.find(i + j * 5) == free.end())
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            some_output = true;
            cout << i / 10 << ":";
            cout << (i % 10 == 0 ? "00" : "30") << "-";
            int f = i + 5 * slots;
            cout << f / 10 << ":";
            cout << (f % 10 == 0 ? "00" : "30");
            cout << endl;
        }
    }
    if (!some_output)
    {
        cout << "No way" << endl;
    }
    return 0;
}
