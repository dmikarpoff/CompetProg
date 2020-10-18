#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>

using namespace std;

double bin(int n, int k, double p) {
    if (n < k)
        return 0.0;
    double res = std::pow(p, k) * std::pow(1.0 - p, n - k);
    for (int j = n; j > n - k; --j)
        res *= j;
    for (int j = 1; j <= k; ++j)
        res /= j;
    return res;
}

int main()
{
    constexpr double p = 0.3;
    constexpr int sample_num = 100;
    double p_lier[sample_num + 1];
    for (int i = 0; i <= sample_num; ++i) {
        p_lier[i] = bin(sample_num, i, p);
    }
    constexpr int upper_limit = 30;
    double grid[sample_num + 1][upper_limit];
    double grid_sum = 0.0;
    for (int lier = 0; lier <= sample_num; ++lier) {
        for (int res = 0; res < upper_limit; ++res) {
            grid[lier][res] = 0.0;
            for (int t_in_l = 0; t_in_l <= min(res, lier); ++t_in_l) {
                int t_men = sample_num - lier;
                int l_in_t = res - t_in_l;
                grid[lier][res] += bin(lier, t_in_l, 0.4) * bin(t_men, l_in_t, 0.2);
            }
            cout << grid[lier][res] << " ";
            grid_sum += p_lier[lier] * grid[lier][res];
        }
        cout << endl;
    }
    cout << grid_sum << endl;
    return 0;
}
