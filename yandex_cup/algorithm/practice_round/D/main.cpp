#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <numeric>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& x : a)
        cin >> x;
    for (auto& x : b)
        cin >> x;

    int max_a = 0;
    for (auto x : a)
        if (x > max_a)
            max_a = x;
    int max_b = 0;
    for (auto x : b)
        if (x > max_b)
            max_b = x;
    const auto l_max = distance(a.begin(), find(a.begin(), a.end(), max_a));
    const auto r_max = distance(find(a.rbegin(), a.rend(), max_a), a.rend() - 1);
    constexpr uint64_t billion = 1000 * 1000 * 1000;
    auto res = accumulate(a.begin(), a.end(), static_cast<uint64_t>(0)) * billion;
    res += (m - 1) * billion * max_a;
    res += accumulate(b.begin(), b.end(), 0);
//    cout << l_max << " " << r_max << endl;
    res += l_max * b.front() + (r_max - l_max) * max_b + (n - 1 - r_max) * b.back();
    cout << res << endl;
    return 0;
}
