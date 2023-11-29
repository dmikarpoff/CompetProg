#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

int main()
{
    int t;
    cin >> t;
    const uint64_t modulo = 1000 * 1000 * 1000 + 7;
    for (int o = 0; o < t; ++o)
    {
        uint64_t n;
        cin >> n;
        // cout << "-----" << endl;
        uint64_t cycle = 2;
        uint64_t ones[100];
        fill(begin(ones), end(ones), 0);
        int pos = 0;
        while (cycle <= n * 2)
        {
            uint64_t full_cycle = (n + 1) / cycle;
            uint64_t rem = (n + 1) % cycle;
            ones[pos] = cycle / 2 * full_cycle;
            if (cycle / 2 < rem)
            {
                ones[pos] += rem - cycle / 2;
            }
            ones[pos] %= modulo;
            ++pos;
            cycle *= 2;
        }
        /*
        for (int i = 0; i < 10; ++i)
            cout << ones[i] << " ";
            */
        //cout << endl;
        uint64_t k = 1;
        uint64_t res = 0;
        for (int i = 0; i < 100; ++i)
        {
            res = (res + ((ones[i] * ones[i] % modulo) * k) % modulo) % modulo;
            k = k * 2 % modulo;
        }
        cout << res << endl;
    }
    return 0;
}
