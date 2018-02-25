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

int get_min_val(size_t l, size_t r, size_t lbound,
                size_t rbound, size_t idx)
{
//    cout << "Getting min val for " << l << " " << r << endl;
//    cout << "On " << lbound << " " << rbound << endl;
//    cout << "With idx = " << idx << endl;
    if (lbound == rbound)
        return seg_tree[idx];
    if (l == lbound && r == rbound)
        return seg_tree[idx];

    size_t mid = (lbound + rbound) / 2;
    int res = 1000 * 1000 * 1000 + 2;
    if (l <= mid && lbound <= mid)
    {
        res = min(res, get_min_val(max<size_t>(lbound, l),
                                   min<size_t>(mid, r),
                                   lbound, mid, 2 * idx));
    }
    if (r > mid && mid + 1 <= rbound)
    {
        res = min(res, get_min_val(max<size_t>(mid + 1, l),
                                   min<size_t>(r, rbound),
                                   mid + 1, rbound, 2 * idx + 1));
    }
//    cout << "Result = " << res << endl;
    return res;
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
        last_c_cost += a[i];
        if (i >= c)
            last_c_cost -= a[i - c];
        costs[i] = costs[i - 1] + a[i];
  //      cout << "Last cost = " << last_c_cost << endl;
        if (i >= c - 1)
        {
            size_t sz = seg_tree.size() / 2;
            int min_val = get_min_val(i - c + 1, i, 0, sz - 1, 1);
            uint64_t sub_cost = (i >= c ? costs[i - c] : 0);
  //          cout << "Min val = " << min_val << endl;
            uint64_t upd_cost = sub_cost + static_cast<uint64_t>(
                                    last_c_cost - min_val);
  //          cout << "Upd. cost = " << upd_cost << endl;
            if (upd_cost < costs[i])
                costs[i] = upd_cost;
        }
//        cout << "i = " << i << "; " << "cost = "
//             << costs[i] << endl;
    }

    cout << costs[n - 1];

    return 0;
}
