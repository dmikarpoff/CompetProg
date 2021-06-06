#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 1; o <= t; ++o) {
        int m;
        cin >> m;
        vector<uint64_t> p(m);
        vector<uint64_t> n(m);
        uint64_t sum = 0;
        for (int i = 0; i < m; ++i) {
            cin >> p[i] >> n[i];
            sum += p[i] * n[i];
        }
        uint64_t gap = 30000;
        uint64_t from = (gap + 2 > sum ? 2 : sum - gap);
        uint64_t res = 0;
        for (uint64_t i = from; i < sum; ++i) {
            uint64_t val = i;
            bool skip = false;
            uint64_t t = 0;
            for (int j = 0; j < m && !skip; ++j) {
                uint64_t f = 0;
                while (val % p[j] == 0) {
                    ++f;
                    val /= p[j];
                }
                if (f > n[i]) {
                    skip = true;
                }
                t += p[j] * (n[j] - f);
            }
            if (!skip && val == 1 && t == i) {
                res = i;
            }
        }
        cout << "Case #" << o << ": " << res;
        cout << endl;
    }
    return 0;
}
