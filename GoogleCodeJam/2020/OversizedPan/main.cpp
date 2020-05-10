#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdint>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int n, d;
        cin >> n >> d;
        vector<uint64_t> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        sort(a.begin(), a.end());
        cout << "Case #" << o + 1 << ": ";
        if (d == 2)
        {
            bool one = false;
            for (size_t i = 0; i + 1 < n; ++i)
            {
                if (a[i] == a[i + 1])
                    one = true;
            }
            cout << (one ? 0 : 1) << endl;
        }
        if (d == 3)
        {
            bool one = false;
            for (size_t i = 0; i + 2 < n; ++i)
            {
                if (a[i] == a[i + 1] && a[i + 1] == a[i + 2])
                    one = true;
            }
            if (one)
            {
                cout << 0 << endl;
            }
            else
            {
                bool f = false;
                for (int i = 0; i < n; ++i)
                    if (a[i] % 2 == 0)
                    {
                        auto v = a[i] / 2;
                        if (binary_search(a.begin(), a.end(), v))
                        {
                            f = true;
                        }
                    }
                cout << (f ? 1 : 2) << endl;
            }
        }
    }
    return 0;
}
