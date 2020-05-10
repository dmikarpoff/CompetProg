#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> mapping;

int dfs(int v, const vector<vector<int>>& adj, vector<int>& p,
        vector<int>& mark)
{
    mark[v] = 1;
    for (auto u : adj[v])
    {
        u = mapping[u];
        if (u == v)
            continue;
        if (mark[u] == 0)
        {
            p[u] = v;
            auto res = dfs(u, adj, p, mark);
            if (res != -1)
            {
                return res;
            }
        }
        else
        {
            if (mark[u] == 2)
                continue;
            if (mark[u] == 1)
            {
                p[u] = v;
                return u;
            }
        }
    }
    mark[v] = 2;
    return -1;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i)
    {
        mapping.push_back(i);
        int val = 0;
        cin >> val;
        while (val != 0)
        {
            if (val != i + 1)
            {
                adj[i].push_back(val - 1);
            }
            cin >> val;
        }
//        sort(adj[i].begin(), adj[i].end());
    }
    vector<int> cycle;
    do {
        cycle.clear();
        vector<int> p(n, -1);
        vector<int> mark(n, 0);
        for (int i = 0; i < n && cycle.empty(); ++i)
        {
            if (mapping[i] != i || mark[i] != 0)
                continue;
            int c = dfs(i, adj, p, mark);
            if (c != -1)
            {
                cycle.push_back(c);
                for (int j = p[c]; j != c; j = p[j])
                    cycle.push_back(j);
                break;
            }
        }
        if (!cycle.empty())
        {
            int l = cycle.front();
//            cout << l << " ";
            for (size_t j = 1; j < cycle.size(); ++j)
            {
                int r = cycle[j];
//                cout << r << " ";
                for (int h = 0; h < n; ++h)
                {
                    if (mapping[h] == r)
                        mapping[h] = l;
                }
                adj[l].insert(adj[l].end(), adj[r].begin(), adj[r].end());
                adj[l].erase(remove_if(adj[l].begin(), adj[l].end(),
                                       [l,r](auto x) {return x == l || x == r;}),
                             adj[l].end()
                           );
                adj[r].clear();
            }
//            cout << endl;
        }
    } while (!cycle.empty());
    vector<int> pw(n, 0);
    for (const auto& a : adj)
    {
        for (auto v : a)
        {
            ++pw[v];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (mapping[i] != i)
            pw[i] = -1;
    }
    auto i = find(pw.begin(), pw.end(), 0);
    if (i == pw.end() || find(i + 1, pw.end(), 0) != pw.end())
    {
        cout << 0 << endl;
        return 0;
    }
    auto r = i - pw.begin();
    for (int i = 0; i < n; ++i)
        if (mapping[i] == r)
            cout << i + 1 << " ";
    cout << 0 << endl;
    return 0;
}
