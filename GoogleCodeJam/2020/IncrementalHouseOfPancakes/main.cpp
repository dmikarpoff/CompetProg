#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
//    int o = 0;
//    for (int ll = 1; ll <= 1000; ++ll)
//    for (int rr = 1; rr <= 1000; ++rr)
    for (int o = 0; o < T; ++o)
    {
//        cout << ll << " " << rr << endl;
        int64_t l /*= ll*/, r/* = rr*/;
        cin >> l >> r;
        int64_t d = abs(l - r);
        int64_t from = 0;
        int64_t to = 2 * 1000 * 1000 * 1000;
        while (from != to)
        {
            auto m = (from + to) / 2;
            if (m * (m + 1) == 2 * d)
            {
                from = m;
                to = m;
            }
            else
            {
                if (m * (m + 1) > 2 * d)
                {
                    to = m;
                }
                else
                {
                    from = m + 1;
                }
            }

        }
        if (from * (from + 1) > 2 * d)
        {
            --from;
        }
        int n = from;
        if (l >= r)
        {
            l -= n * (n + 1) / 2;
        }
        else
        {
            r -= n * (n + 1) / 2;
        }

        from = 0;
        to = 1000 * 1000 * 1000;
//        cout << n << " " << l << " " << r << endl;
        while (from != to)
        {
            auto m = (from + to) / 2;
            if ((n + m) * m == max(l, r))
            {
                from = m;
                to = m;
            }
            else
            {
                if ((n + m) * m > max(l, r))
                {
                    to = m;
                }
                else
                {
                    from = m + 1;
                }
            }
        }
        int64_t k_max = from;
        if ((n + from) * from > max(l, r))
        {
            k_max--;
        }

        from = 1;
        to = 1000 * 1000 * 1000;
        while (from != to)
        {
            auto m = (from + to) / 2;
            if ((n + m + 1) * m == min(l, r))
            {
                from = m;
                to = m;
            }
            else
            {
                if ((n + m + 1) * m > min(l, r))
                {
                    to = m;
                }
                else
                {
                    from = m + 1;
                }
            }
        }
        int64_t k_min = from;
        if ((n + from + 1) * from > min(l, r))
        {
            k_min--;
        }
        int64_t k = min(k_max, k_min);
        // cout << k << endl;
        if (l >= r)
        {
            l -= (n + k) * k;
            r -= (n + k + 1) * k;
        }
        else
        {
            r -= (n + k) * k;
            l -= (n + k + 1) * k;
        }
        n += 2 * k;
        if (l >= r)
        {
            if (l > n)
            {
                ++n;
                l -= n;
            }
        }
        else {
            if (r > n)
            {
                ++n;
                r -= n;
            }
        }

        cout << "Case #" << o + 1 << ": ";
        cout << n << " " << l << " " << r;
        cout << endl;
        //++o;
    }
    return 0;
}
