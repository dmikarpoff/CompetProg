#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<bool> used;
vector<vector<int>> adj;

void dfs(int x)
{
  used[x] = true;
  for (auto d : adj[x])
  {
    if (!used[d])
      dfs(d);
  }
}

int main()
{
    int n, m;
    cin >> m >> n;
    int res = 0;
    adj.resize(m + 1);
    used.resize(m + 1, false);
    for (int i = 1; i <= m; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        int x;
        cin >> x;
        if (x == i)
          continue;
        ++res;
        adj[x].push_back(i);
      }
    }

    for (int i = 1; i <= m; ++i)
      if (!used[i] && !adj[i].empty())
      {
        res++;
        dfs(i);
      }

    cout << max(0, res - 1) << endl;
    return 0;
}
