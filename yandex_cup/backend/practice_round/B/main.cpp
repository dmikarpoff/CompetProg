#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <limits>

int main()
{
    int n, x, k;
    std::cin >> n >> x >> k;
    std::vector<int> a;
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        auto it = std::lower_bound(a.begin(), a.end(), t, [x](int v, int t) {return v % x < t % x;});
//        std::cout << (it == a.end() ? "not found" : std::to_string(*it)) << std::endl;
        if (it == a.end() || *it % x != t % x) {
            a.insert(it, t);
        } else if (t < *it) {
            *it = t;
        }
    }
    std::sort(a.begin(), a.end());
    int64_t l = 0;
    int64_t r = std::numeric_limits<int64_t>::max();
    while (l < r) {
        int64_t mid = (l + r) / 2;
        int64_t cnt = 0;
        for (auto e : a) {
            if (e <= mid) {
                cnt += (mid - e) / x + 1;
                if (cnt > k) {
                    break;
                }
            }
        }
//        std::cout << l << " " << r << " " << cnt << std::endl;
        if (cnt == k) {
            l = r = mid;
        } else {
            if (cnt < k) {
                l = mid;
            } else {
                r = mid;
            }
        }
    }
    int64_t best = 0;
    for (auto e : a) {
        if (e <= l) {
            int64_t m = (l - e) / x;
            int64_t v = e + m * x;
            if (l - v < l - best) {
                best = v;
            }
        }
    }
    if (best > l) {
        return -1;
    }
    std::cout << best << std::endl;
    return 0;
}
