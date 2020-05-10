#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Strength
{
    int a;
    int b;
    int c;
};

bool operator<(const Strength& lhs, const Strength& rhs)
{
    int pt = 0;
    if (lhs.a < rhs.a)
        ++pt;
    if (lhs.b < rhs.b)
        ++pt;
    if (lhs.c < rhs.c)
        ++pt;
    return pt >= 2;
}

void dfs(int v, const vector<vector<int>>& adj, vector<char>& used)
{
    used[v] = 1;
    for (auto x : adj[v])
        if (used[x] == 0)
        {
            dfs(x, adj, used);
        }
}

int main()
{
    vector<string> names;
    vector<Strength> strength;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string name;
        int a, b, c;
        cin >> name >> a >> b >> c;
        names.emplace_back(move(name));
        strength.push_back({a, b, c});
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            if (strength[j] < strength[i])
                adj[i].push_back(j);
    }
    for (int i = 0; i < n; ++i)
    {
        vector<char> used(n, 0);
        dfs(i, adj, used);
        if (find(used.begin(), used.end(), 0) == used.end())
        {
            cout << names[i] << endl;
        }
    }
    return 0;
}
