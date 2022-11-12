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
        int n, p;
        cin >> n >> p;
        vector<uint64_t> cur_cnt(p, 0), prev_cnt(p, 0);
        vector<int> cur_val(p, 0), prev_val(p, 0);
        for (int i = 0; i < n; ++i)
        {
            vector<int> x(p);
            int max_val = 0;
            int min_val = 1000 * 1000 * 1000 + 1;
            for (int j = 0; j < p; ++j)
            {
                cin >> x[j];
                max_val = max(max_val, x[j]);
                min_val = min(min_val, x[j]);
            }
            for (int j = 0; j < p; ++j)
            {
                uint64_t best = 1000 * 1000 * 1000 * 1000 * 1000;
                for (int h = 0; h < p; ++h)
                {
                    uint64_t left_max = abs(max_val - prev_val[h]) + abs(min_val - x[j]);
                    uint64_t right_max = abs(max_val - x[j]) + abs(min_val - prev_val[h]);
                    uint64_t local_cost = min(left_max, right_max) + max_val - min_val;
                    if (cur_cnt[j] == 0 || cur_cnt[j] > prev_cnt[h] + local_cost)
                    {
                        cur_cnt[j] = prev_cnt[h] + local_cost;
                        cur_val[j] = x[j];
                    }
                }
            }
            swap(prev_val, cur_val);
            swap(cur_cnt, prev_cnt);
            cur_cnt.assign(p, 0);
        }
        uint64_t res = prev_cnt[0];
        for (auto x : prev_cnt)
        {
            res = min(res, x);
        }
        cout << "Case #" << o + 1 << ": ";
        cout << res;
        cout << endl;
    }
    return 0;
}
