#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <cstdio>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        uint64_t n, k;
        scanf("%ld%ld", &n, &k);
        double d = sqrt((2 * n + 3) * (2 * n + 3) - 8 * k);
        double r = (2 * n + 3 - d) / 2.0;
        //cout << "r = " << r << endl;
        uint64_t p = static_cast<int64_t>(r);
        if ((2 * n + 2 - p) * (p + 1) < 2 * k)
        {
            ++p;
        }
        if ((2 * n + 3 - p) * p >= 2 * k)
        {
            --p;
        }
        // cout << "p = " << p << endl;
        auto cnt = (2 * n + 3 - p) * p / 2;
        //cout << "-- " << cnt << endl;
        uint64_t x = p;
        uint64_t y = k - cnt + p - 1;
        printf("%d %d\n", min(x, y), max(x, y));
    }
    return 0;
}
