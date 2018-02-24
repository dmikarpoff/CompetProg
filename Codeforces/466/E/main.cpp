#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

vector<int> seg_tree;

void make_seg_tree(const vector<int>& a)
{
    uint64_t sz = 1;
    while (sz < a.size())
        sz <<= 1;
    seg_tree.resize(2 * sz, 1000 * 1000 * 1000 + 1);
    for (size_t i = sz; i < 2 * sz; ++i)
        seg_tree[i] = a[i - sz];
    for (size_t i = sz - 1; i > 0; --i)
        seg_tree[i] = min(seg_tree[2 * i], seg_tree[2 * i + 1]);
}

int get_min_val(size_t l, size_t r)
{

}

int main()
{
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<uint64_t> costs(n, 0);
    costs[0] = a[0];
    uint64_t last_c_cost = a[0];
    make_seg_tree(a);
    for (int i = 1; i < n; ++i)
    {
        if (i > c)
        {
            last_c_cost -= a[i - c - 1];
            last_c_cost += a[i];
        }
        costs[i] = costs[i - 1] + a[i];
        if (i > c)
        {
            uint64_t upd_cost = costs[i - c - 1] + last_c_cost - get_min_val(i - c, i);
            if (upd_cost < costs[i])
                costs[i] = upd_cost;
        }
    }

    cout << costs[n - 1];

    return 0;
}
