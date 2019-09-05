#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<int> marks;

void dfs(int x)
{
  marks[x] = 1;
  for (auto y : adj[x])
    if (marks[y] == 0)
      dfs(y);
}

int main()
{
    int n, k, m;
    cin >> n >> k >> m;
    adj.resize(n + 1);
    marks.resize(n + 1, 0);
    for (int i = 0; i < k; ++i)
    {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    for (int i = 0; i < m; ++i)
    {
      int u,v;
      cin >> u >> v;
    }
    int comp = 0;
    for (int i = 1; i <= n; ++i)
      if (marks[i] == 0)
      {
        dfs(i);
        ++comp;
      }
    cout << comp - 1 << endl;
    return 0;
}
