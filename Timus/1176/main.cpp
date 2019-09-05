#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> path;
vector<vector<int>> adj;
vector<vector<int>> removed;

void findPath(int v)
{
  for (auto u : adj[v])
  {
    if (removed[v][u] == 0)
    {
      removed[v][u] = 1;
      findPath(u);
    }
  }
  path.push_back(v);
}

int main()
{
    int n, a;
    cin >> n >> a;
    adj.resize(n + 1);
    removed.resize(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
      {
        int val;
        cin >> val;
        removed[i][j] = val;
        if (val == 0 && i != j)
          adj[i].push_back(j);
      }
    findPath(a);
    reverse(path.begin(), path.end());
    for (size_t i = 0; i + 1 < path.size(); ++i)
      cout << path[i] << " " << path[i + 1] << endl;
    return 0;
}
