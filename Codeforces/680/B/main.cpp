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
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        std::cout << std::max(c + d, b + a) << std::endl;
    }
    return 0;
}
