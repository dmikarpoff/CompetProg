#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<uint64_t> v(n);
    vector<uint64_t> t(n);
    for (int i = 0; i < n; ++i)
        scanf("%I64d", &v[i]);
    for (int i = 0; i < n; ++i)
        scanf("%I64d", &t[i]);
    uint64_t prev_bound = 0;
    multiset<uint64_t> data;
    for (size_t i = 0; i < n; ++i)
    {
        uint64_t cur_bound = t[i] + prev_bound;
        uint64_t val = prev_bound + v[i];
        data.insert(val);

        if (t[i] == 0)
        {
            cout << 0 << " ";
            continue;
        }
        auto left = data.lower_bound(prev_bound);
        auto right = data.lower_bound(cur_bound);
        uint64_t total = 0;
        for (auto j = left; j != right; ++j)
            total += (*j - prev_bound);
        //auto cnt = distance(right, data.end());
        data.erase(data.begin(), right);
        total += data.size() * t[i];

        printf("%I64d ", total);

        prev_bound = cur_bound;
    }
    return 0;
}
