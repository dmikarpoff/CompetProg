#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Node
{
    int parent = -1;
    vector<int> children;
    bool red = false;
    int cnt = 0;
    int limit;
    int desc_count = 0;
    int xr = 0;
    set<int> red_desc;
};

Node nodes[100001];

void calc(int v)
{
    for (auto x : nodes[v].children)
    {
        calc(x);
        nodes[v].desc_count += nodes[x].desc_count;
        nodes[v].xr ^= nodes[x].xr;
    }
    nodes[v].desc_count++;
    nodes[v].xr ^= v;
}

int main()
{
    int n;
    cin >> n;
    int r = -1;
    for (int i = 0; i < n; ++i)
    {
        int idx, l;
        cin >> idx >> l;
        if (r < 0)
        {
            r = idx;
        }
        nodes[idx].limit = l;
    }
    for (int i = 0; i < n - 1; ++i)
    {
        int f, t;
        cin >> f >> t;
        nodes[t].parent = f;
        nodes[f].children.push_back(t);
    }
    calc(r);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int idx, d;
        cin >> idx >> d;
        nodes[idx].cnt += d;
        bool was_red = false;
        int xx = idx;
        while (xx != -1)
        {
            if (nodes[xx].red)
            {
                was_red = true;
                break;
            }
            xx = nodes[xx].parent;
        }
        if (nodes[idx].cnt >= nodes[idx].limit && !nodes[idx].red)
        {
            nodes[idx].red = true;
            const auto& old_red = nodes[idx].red_desc;
            int cur = nodes[idx].parent;
            while (cur != -1)
            {
                for (auto x : old_red)
                {
                    nodes[cur].red_desc.erase(x);
                }
                nodes[cur].red_desc.insert(idx);
                if (nodes[cur].red)
                {
                    break;
                }
                cur = nodes[cur].parent;
            }
        }
        else if (nodes[idx].cnt < nodes[idx].limit && nodes[idx].red)
        {
            nodes[idx].red = false;
            const auto& old_red = nodes[idx].red_desc;
            int cur = nodes[idx].parent;
            while (cur != -1)
            {
                nodes[cur].red_desc.erase(idx);
                for (auto x : old_red)
                {
                    nodes[cur].red_desc.insert(x);
                }
                if (nodes[cur].red)
                {
                    break;
                }
                cur = nodes[cur].parent;
            }
        }
        bool is_red = false;
        xx = idx;
        while (xx != -1)
        {
            if (nodes[xx].red)
            {
                is_red = true;
                break;
            }
            xx = nodes[xx].parent;
        }
        if (is_red == was_red)
        {
            cout << "0 0" << endl;
        }
        else
        {
            int cnt = nodes[idx].desc_count;
            int xr = nodes[idx].xr;
            // cout << "### ";
            for (auto x : nodes[idx].red_desc)
            {
                // cout << x << " ";
                cnt -= nodes[x].desc_count;
                xr ^= nodes[x].xr;
            }
            // cout << endl;
            cout << cnt << " " << xr << endl;
        }
    }

    return 0;
}
