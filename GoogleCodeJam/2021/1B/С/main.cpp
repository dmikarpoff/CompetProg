#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

double dp[21][21][16][16];

int occupied_tower(int full, int prefull, int t1, int t2)
{
    return full + prefull + (t1 > 0 ? 1 : 0) + (t2 > 0 ? 1 : 0);
}

int main()
{
    uint64_t t, n, b, p;
    cin >> t >> n >> b >> p;
    for (int i = 0; i <= 20; ++i)
    {
        for (int j = 0; j <= 20; ++j)
        {
            for (int h = 0; h <= 15; ++h)
            {
                for (int k = 0; k <= 15; ++k)
                {
                    dp[i][j][k][h] = -1.0;
                }
            }
        }
    }

    auto is_idx_valid = [n, b](int full, int prefull, int t1, int t2)
    {
        if (t2 < t1)
        {
            return false;
        }
        if (full < 0 || full > n || prefull < 0 || prefull > n ||
            t1 < 0 || t1 > n || t2 < 0 || t2 > n)
        {
            return false;
        }
        auto total = full + prefull + (t1 > 0 ? 1 : 0) + (t2 > 0 ? 1 : 0);
        if (total < 0 || total > n)
        {
            return false;
        }
        return true;
    };

    dp[0][0][0][0] = 0;
    for (int f = 0; f <= n; ++f)
    {
        for (int p = 0; p <= n; ++p)
        {
            for (int t1 = 0; t1 <= b - 2; ++t1)
            {
                for (int t2 = t1; t2 <= b - 2; ++t2)
                {
                    if (!is_idx_valid(f, p, t1, t2))
                    {
                        continue;
                    }
                    for (int d = 0; d <= 10; ++d)
                    {
                        double val = 0.0;
                        if (is_idx_valid(f - 1, p + 1, t1, t2))
                        {
                            val = max(val, dp[f - 1][p + 1][t1][t2] + pow(10.0, b - 1) * d);
                        }
                        if (t1 == 0 && is_idx_valid(f, p - 1, t2, b - 2))
                        {
                            val = max(val, dp[f][p - 1][t2][b - 2] + pow(10.0, b - 2) * d);
                        }
                        if (is_idx_valid(f, p, t1, t2 - 1))
                        {
                            val = max(val, dp[f][p][t1][t2 - 1] + pow(10.0, t2 - 1) * d);
                        }
                        if (is_idx_valid(f, p, t1 - 1, t2))
                        {
                            val = max(val, dp[f][p][t1 - 1][t2] + pow(10.0, t1 - 1) * d);
                        }
                        dp[f][p][t1][t2] += 0.1 * val;
                    }
                }
            }
        }
    }
    cout << "E = " << dp[n][0][0][0] << endl;
    for (int o = 0; o < t; ++o)
    {
        array<int, 10> counter;
        counter.fill(0);
        vector<size_t> tower(n, 0);
        int full = 0;
        for (int i = 0; i < n * b; ++i)
        {
            int d;
            cin >> d;
            double less_than = n * b * d / 10.0 - accumulate(counter.begin(), counter.begin() + d, 0);
            double rem = n * b - i;
            // cout << "less_than = " << less_than << endl;
            // cout << "rem = " << rem << endl;
            double less_rate = less_than / rem;
            // cout << "less_rate = " << less_rate << endl;
            size_t ord = static_cast<int>((n - full) * less_rate);
            ord = min<size_t>(ord + 1, n - full - 1);
            vector<pair<size_t, size_t>> sz_idx;
            for (size_t j = 0; j < tower.size(); ++j)
            {
                sz_idx.emplace_back(tower[j], j + 1);
            }
            sort(sz_idx.begin(), sz_idx.end());
            size_t a = sz_idx[ord].second;
            cout << a << endl;
            tower[a - 1]++;
            if (tower[a - 1] == b)
            {
                full++;
            }
        }
    }
    int res;
    cin >> res;
    //assert(res > 0);
    return 0;
}
