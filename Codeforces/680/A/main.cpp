#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <string>

#include <cmath>
#include <algorithm>
#include <numeric>
#include <cstdint>

int main()
{
    int t;
    std::cin >> t;
    for (int o = 0; o < t; ++o) {
        int n, x;
        std::cin >> n >> x;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        bool failed = false;
        for (int i = 0; i < n; ++i) {
            int v;
            std::cin >> v;
            if (a[n - i - 1] + v > x) {
                failed = true;
            }
        }
        std::cout << (failed ? "No" : "Yes") << std::endl;
    }
    return 0;
}
