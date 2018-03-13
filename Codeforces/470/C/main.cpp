#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<uint64_t> v(n);
    vector<uint64_t> t(n);
    vector<uint64_t> sum(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    for (int i = 0; i < n; ++i)
        cin >> t[i];
    uint64_t prev_bound = 0;
    vector<uint64_t> data;
    data.reserve(n);
    for (size_t i = 0; i < n; ++i)
    {
//        cout << "----------" << endl;
//        cout << "it " << i << endl;
        uint64_t cur_bound = t[i] + prev_bound;
        uint64_t val = prev_bound + v[i];
        auto it = std::lower_bound(data.begin(), data.end(), val);
        data.insert(it, val);
/*
        for (auto v : data)
            cout << v << " ";
        cout << endl;
*/
        if (t[i] == 0)
        {
            cout << 0 << " ";
            continue;
        }
        auto left = upper_bound(data.begin(), data.end(), prev_bound);
        auto right = lower_bound(data.begin(), data.end(), cur_bound);
        uint64_t total = 0;
        for (auto j = left; j != right; ++j)
            total += (*j - prev_bound);
        auto cnt = distance(right, data.end());
        total += cnt * t[i];

        cout << total << " ";

        prev_bound = cur_bound;
    }
    return 0;
}
