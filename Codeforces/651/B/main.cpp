#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int n;
        cin >> n;
        vector<int> a(2 * n);
        for (int i = 0; i < 2 * n; ++i)
        {
            cin >> a[i];
        }
        auto p = a.begin();
        int cnt = 0;
//        cout << "Even: " << endl;
        while (true)
        {
            if (cnt == n - 1)
            {
                break;
            }
            auto l = find_if(p, a.end(), [](auto x) {return x % 2 == 0;});
            if (l == a.end())
                break;
            auto r = find_if(l + 1, a.end(), [](auto x) {return x % 2 == 0;});
            if (r == a.end())
                break;
            cout << l - a.begin() + 1 << " " << r - a.begin() + 1 << endl;
            p = r + 1;
            ++cnt;
        }
//        cout << "Odd: " << endl;
        p = a.begin();
        while (true)
        {
            if (cnt == n - 1)
            {
                break;
            }
            auto l = find_if(p, a.end(), [](auto x) {return x % 2 == 1;});
            if (l == a.end())
                break;
            auto r = find_if(l + 1, a.end(), [](auto x) {return x % 2 == 1;});
            if (r == a.end())
                break;
            cout << l - a.begin() + 1 << " " << r - a.begin() + 1 << endl;
            p = r + 1;
            ++cnt;
        }
    }
    return 0;
}
