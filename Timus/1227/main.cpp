#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parent;
vector<int> dist;
vector<int> comp;
vector<vector<int>> adj;
int num_comp = 0;

bool dfs(int v)
{
    for (int i = 1; i < adj[v].size(); ++i)
        if (adj[v][i] != -1 && parent[v] != i)
        {
            if (parent[i] != -1)
            {
                return true;
            }
            parent[i] = v;
            comp[i] = comp[v];
            dist[i] = dist[v] + adj[v][i];
            if (dfs(i))
            {
                return true;
            }
        }
    return false;
}

int main()
{
    int m, n, s;
    cin >> m >> n >> s;
    parent.resize(m + 1, -1);
    dist.resize(m + 1, -1);
    comp.resize(m + 1, -1);
    adj.resize(m + 1, vector<int>(m + 1, -1));
    for (int i = 0; i < n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == b || adj[a][b] != -1)
        {
            cout << "YES" << endl;
            return 0;
        }
        adj[a][b] = c;
        adj[b][a] = c;
    }

    for (int i = 1; i <= m; ++i)
    {
        if (parent[i] == -1)
        {
            parent[i] = i;
            dist[i] = 0;
            comp[i] = num_comp;
            if (dfs(i))
            {
                cout << "YES" << endl;
                return 0;
            }
            ++num_comp;
        }
    }
    vector<int> m_in_comp(num_comp, -1);
    for (int i = 1; i <= m; ++i)
    {
        auto c = comp[i];
        if (m_in_comp[c] == -1 || dist[m_in_comp[c]] < dist[i])
        {
            m_in_comp[c] = i;
        }
    }

    parent.assign(m + 1, -1);
    dist.assign(m + 1, -1);
    for (auto v : m_in_comp)
    {
        parent[v] = v;
        dist[v] = 0;
        dfs(v);
    }
    auto m_val = 0;
    for (auto v : dist)
    {
        m_val = max(v, m_val);
    }
    if (m_val >= s)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}
