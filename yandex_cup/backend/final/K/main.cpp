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
    int m, x;
    std::cin >> m >> x;
    std::set<int> r;
    std::set<int> hits;
    auto it = r.begin();
    int it_pos = -1;
    for (int i = 0; i < m; ++i) {
        int n;
        std::cin >> n;
        int expected_size = n + r.size();
        int expected_hits = expected_size * x / 100 + (expected_size * x % 100 == 0 ? 0 : 1);
//        std::cout << "e = " << expected_hits << std::endl;
        std::vector<int> a(n);
        for (int j = 0; j < n; ++j) {
            int x;
            std::cin >> a[j];
        }
        sort(a.begin(), a.end());
        for (auto x : a) {
            r.insert(x);
            if (it_pos == -1) {
                it_pos = 0;
                it = r.begin();
                hits.insert(x);
                continue;
            }

            if (x < *it) {
                hits.insert(x);
                if (it_pos + 1 < expected_hits) {
                    ++it_pos;
                } else {
                    --it;
                }
                continue;
            }

//            std::cout << "compare " << it_pos << " ?< " << expected_hits << std::endl;
            if (it_pos < expected_hits - 1) {
                ++it;
                while (it != r.end() && *it <= x && it_pos < expected_hits - 1) {
                    hits.insert(*it);
                    ++it;
                    ++it_pos;
                }
                --it;
                //--it_pos;
            }
            //std::cout << "pos = " << it_pos << " " << (it == r.end() ? -1 : *it) << std::endl;
        }
        while (it_pos < expected_hits - 1) {
            ++it_pos;
            ++it;
            hits.insert(*it);
        }
        /*
        std::cout << "hits: ";
        for (auto x : hits) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        */
        std::cout << hits.size() << std::endl;
    }
    return 0;
}
