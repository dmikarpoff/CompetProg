#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int cnt[3] = {0, 0, 0};
    int min_val = 100001;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        if (x < min_val)
        {
                if (min_val != 100001)
                {
                cnt[2] = cnt[2 - (min_val - x)];
                if (x + 1 == min_val)
                    cnt[1] = cnt[0];
                else
                    cnt[1] = 0;
                cnt[0] = 0;
            }
            min_val = x;
        }
        cnt[x - min_val]++;
    }
    if (cnt[2] == 0)
    {
        cout << n << endl;
        for (int i = 0; i < cnt[0]; ++i)
            cout << min_val << " ";
        for (int i = 0; i < cnt[1]; ++i)
            cout << min_val + 1 << " ";
        for (int i = 0; i < cnt[2]; ++i)
            cout << min_val + 2 << " ";
        return 0;
    }
    int32_t val = cnt[2]  * 2 + cnt[1];
    int best_fail = n;
    int best_cnt[3] = {cnt[0], cnt[1], cnt[2]};
//    cout << "min_val = " << min_val << endl;
//    cout << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
    for (int i = 0; i <= n; ++i)
    {
        int rem = n - i;
        int32_t t = val - rem;
        if (t >= 0 && t <= rem)
        {
            int fail_val = min(cnt[0], i) +
                           min(cnt[1], (rem - t)) +
                           min(cnt[2], t);
            if (fail_val < best_fail)
            {
                best_fail = fail_val;
                best_cnt[0] = i;
                best_cnt[1] = rem - t;
                best_cnt[2] = t;
            }
        }
    }
    cout << best_fail << endl;
    for (int i = 0; i < best_cnt[0]; ++i)
        cout << min_val << " ";
    for (int i = 0; i < best_cnt[1]; ++i)
        cout << min_val + 1 << " ";
    for (int i = 0; i < best_cnt[2]; ++i)
        cout << min_val + 2 << " ";
    return 0;
}
