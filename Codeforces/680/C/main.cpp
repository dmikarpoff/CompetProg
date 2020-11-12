#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

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

//std::vector<uint64_t> primes;

std::map<int64_t, int> decomp(int64_t x) {
    std::map<int64_t, int> res;
    for (int64_t i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            x /= i;
            res[i] += 1;
        }
    }
    if (x > 1) {
        res[x] += 1;
    }
    return res;
}

/*
void push_prime(uint64_t x) {
    for (size_t i = 0; i < primes.size(); ++i) {
        auto p = primes[i];
        if (p * p > x) {
            break;
        }
        if (x % p == 0) {
            return;
        }
    }
    primes.push_back(x);
}
*/

int main()
{
    int t;
    std::cin >> t;
    for (int o = 0; o < t; ++o) {
        int64_t p, q;
        std::cin >> p >> q;
        //auto p_div = decomp(p);
        auto q_div = decomp(q);
        /*
        std::cout << "P decomp" << std::endl;
        for (auto x : p_div) {
            std::cout << x.first << " " << x.second << std::endl;
        }
        std::cout << "Q decomp" << std::endl;
        for (auto x : q_div) {
            std::cout << x.first << " " << x.second << std::endl;
        }
        */
        int64_t res = 1;
        for (const auto& d : q_div) {
            int64_t copy_p = p;
            int p_cnt = 0;
            while (copy_p % d.first == 0) {
                copy_p /= d.first;
                ++p_cnt;
            }
            int64_t x = p;
            if (p_cnt >= d.second) {
                int cnt = p_cnt - d.second + 1;
                for (int i = 0; i < cnt; ++i) {
                    x /= d.first;
                }
            }
            res = std::max(x, res);
        }
        std::cout << res << std::endl;
    }
    return 0;
}
