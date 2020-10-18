#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o) {
        int n, x;
        cin >> n >> x;
        bool exists = false;
        int64_t sum = 0;
        int left = -1;
        int right = -1;
        for (int i = 0; i < n; ++i)
        {
            int64_t v;
            cin >> v;
            sum += v;
            if (v % x != 0)
            {
                if (left == -1)
                {
                    left = i;
                }
                right = i;
            }
        }

        if (sum % x == 0)
        {
            cout << (left == -1 ? - 1 : max(n - left - 1, right)) << endl;
            continue;
        }
        cout << n << endl;
    }
    return 0;
}
