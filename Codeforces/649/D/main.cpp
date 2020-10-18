#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> adj[100002];
int used[100002];
vector<int> p;
vector<int> min_cycle;
int n, m, k;

void dfs(int v)
{
    if (!min_cycle.empty())
    {
        return;
    }
    used[v] = 1;
//    cout << "Starting search from " << v << endl;
    for (auto x : adj[v])
    {
        if (used[x] == 1 && x != p[v])
        {
            vector<int> cycle;
            cycle.push_back(x);
//            cout << "Searching cycle to " << x << endl;
            int t = v;
//            cout << "Searching cycle from " << t << endl;
            while (t != x)
            {
//                cout << t << endl;
                cycle.push_back(t);
                t = p[t];
            }
            if (min_cycle.empty() || min_cycle.size() > cycle.size())
            {
                min_cycle = move(cycle);
            }
        }
    }
    if (!min_cycle.empty())
    {
        return;
    }
    for (auto x : adj[v])
    {
        if (used[x] == 0)
        {
            p[x] = v;
            dfs(x);
        }
    }

    used[v] = 2;
//    cout << "Search from " << v << " finished" << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    p.resize(n, -1);
    dfs(0);
    if (!min_cycle.empty())
    {
//        cout << "--" << min_cycle.size() << endl;
        if (min_cycle.size() <= k)
        {
            cout << 2 << endl;
            cout << min_cycle.size() << endl;
            for (auto x : min_cycle)
            {
                cout << x + 1 << " ";
            }
            cout << endl;
            return 0;
        }
        cout << 1 << endl;
        int cnt = k / 2 + (k % 2 ? 1 : 0);
        for (int i = 0, j = 0; i < cnt; ++i, j += 2)
        {
            cout << min_cycle[j] + 1 << " ";
        }
        cout << endl;
        return 0;
    }
    cout << 1 << endl;
    int cnt = k / 2 + (k % 2 ? 1 : 0);
    vector<int> color(n, -1);
    color[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        for (auto v : adj[u])
        {
            if (color[v] == -1)
            {
                q.push(v);
                color[v] = 1 - color[u];
            }
        }
    }
    auto zero_cnt = count(color.begin(), color.end(), 0);
    int key = 0;
    if (zero_cnt < cnt)
    {
        key = 1;
    }
    int j = -1;
    for (int i = 0; i < cnt; ++i)
    {
        ++j;
        while (color[j] != key)
        {
            ++j;
            if (j >= n)
            {
                return -1;
            }
        }
        cout << j + 1 << " ";
    }
    return 0;
}
