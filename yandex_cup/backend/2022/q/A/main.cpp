#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

struct Node
{
    uint64_t mi{0};
    uint64_t ma{0};
    uint64_t mi_idx{1};
    uint64_t ma_idx{1};
};

std::vector<uint64_t> r;
std::vector<std::set<int>> a;

void update(std::vector<Node>& seg, uint64_t cur_idx, uint64_t val)
{
    seg[cur_idx].ma = val;
    seg[cur_idx].mi = val;
    while (cur_idx != 1)
    {
        uint64_t next_idx = cur_idx / 2;
        uint64_t left = 2 * next_idx;
        uint64_t right = 2 * next_idx + 1;
        // update max
        if (seg[left].ma >= seg[right].ma)
        {
            seg[next_idx].ma = seg[left].ma;
            seg[next_idx].ma_idx = seg[left].ma_idx;
        }
        else
        {
            seg[next_idx].ma = seg[right].ma;
            seg[next_idx].ma_idx = seg[right].ma_idx;
        }
        // update min
        if (seg[left].mi <= seg[right].mi)
        {
            seg[next_idx].mi = seg[left].mi;
            seg[next_idx].mi_idx = seg[left].mi_idx;
        }
        else
        {
            seg[next_idx].mi = seg[right].mi;
            seg[next_idx].mi_idx = seg[right].mi_idx;
        }
        cur_idx = next_idx;
    }
    /*
    for (int i = 0; i < seg.size(); ++i)
    {
        cout << i << ":" << endl;
        cout << "\tmax = " << seg[i].ma << " " << seg[i].ma_idx << endl;
        cout << "\tmin = " << seg[i].mi << " " << seg[i].mi_idx << endl;
    }
    */
}


int main()
{
    uint64_t n, m, q;
    std::cin >> n >> m >> q;
    r.resize(n + 1, 0);
    a.resize(n + 1);
    uint64_t offset = 1;
    while (offset < n)
    {
        offset *= 2;
    }
    std::vector<Node> seg(2 * offset, Node());
    for (uint64_t i = 0; i < n; ++i)
    {
        seg[offset + i].ma = 0;
        seg[offset + i].mi = 0;
        seg[offset + i].ma_idx = i + 1;
        seg[offset + i].mi_idx = i + 1;
    }
    for (uint64_t i = offset + n; i < seg.size(); ++i)
    {
        seg[i].mi = static_cast<uint64_t>(1000 * 1000 * 1000) * static_cast<uint64_t>(1000 * 1000);
        seg[i].ma = 0;
        seg[i].mi_idx = i;
        seg[i].ma_idx = i;
    }
    for (int i = offset - 1; i > 0; --i)
    {
        int left = 2 * i;
        int right = 2 * i + 1;
        // update max
        if (seg[left].ma >= seg[right].ma)
        {
            seg[i].ma = seg[left].ma;
            seg[i].ma_idx = seg[left].ma_idx;
        }
        else
        {
            seg[i].ma = seg[right].ma;
            seg[i].ma_idx = seg[right].ma_idx;
        }
        // update min
        if (seg[left].mi <= seg[right].mi)
        {
            seg[i].mi = seg[left].mi;
            seg[i].mi_idx = seg[left].mi_idx;
        }
        else
        {
            seg[i].mi = seg[right].mi;
            seg[i].mi_idx = seg[right].mi_idx;
        }
    }
    for (uint64_t h = 0; h < q; ++h)
    {
        std::string command;
        std::cin >> command;
        if (command == "DISABLE")
        {
            int i, j;
            std::cin >> i >> j;
            a[i].insert(j);
            if (m < a[i].size())
            {
                return -1;
            }
            update(seg, offset + i - 1, r[i] * static_cast<uint64_t>(m - a[i].size()));
            continue;
        }
        if (command == "RESET")
        {
            int i;
            std::cin >> i;
            ++r[i];
            a[i].clear();
            update(seg, offset + i - 1, r[i] * static_cast<uint64_t>(m - a[i].size()));
            continue;
        }
        if (command == "GETMAX")
        {
            if (seg[1].ma_idx > n || seg[1].ma_idx == 0)
            {
                return -1;
            }
            std::cout << seg[1].ma_idx << std::endl;
            continue;
        }
        if (command == "GETMIN")
        {
            if (seg[1].mi_idx > n || seg[1].mi_idx == 0)
            {
                return -1;
            }
            std::cout << seg[1].mi_idx << std::endl;
            continue;
        }
        return -1;
    }
    return 0;
}
