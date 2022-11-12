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
        vector<int> d(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> d[i];
        }
        int l = 0, r = n - 1;
        int res = 0;
        int last_d = 0;
        while (l <= r)
        {
            int v = min(d[l], d[r]);
            if (d[l] < d[r])
            {
                ++l;
            }
            else
            {
                --r;
            }
            if (v >= last_d)
            {
                ++res;
            }
            last_d = max(last_d, v);
        }
        cout << "Case #" << o + 1 << ": " << res;
        cout << endl;
    }
    return 0;
}
