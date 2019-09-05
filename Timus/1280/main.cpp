#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> mark;
vector<int> used;

bool dfs(int v)
{
  used[v] = 1;
  for (auto x : adj[v])
  {
    if (used[x] == 1 || mark[x] < mark[v])
      return false;
    if (used[x] == 0 && !dfs(x))
      return false;
  }
  used[v] = 2;
  return true;
}

int main()
{
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    mark.resize(n + 1, -1);
    used.resize(n + 1, 0);
    std::vector<int> in(n + 1, 0);
    set<pair<int, int>> edge;
    for (int i = 0; i < m; ++i)
    {
      int u, v;
      cin >> u >> v;
      if (edge.find(make_pair(u, v)) != edge.end())
        continue;
      adj[u].push_back(v);
      in[v]++;
    }
    for (int i = 1; i <= n; ++i)
    {
      int v;
      cin >> v;
      mark[v] = i;
    }
    for (int i = 1; i <= n; ++i)
      if (in[i] == 0 && !dfs(i))
      {
        cout << "NO" << endl;
        return 0;
      }
//    cout << "Checking if all visited" << endl;
    if (all_of(used.begin() + 1, used.end(), [](int v) {return v != 0;}))
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
    return 0;
}
