#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(2 * n + 1);
    for (int i = 0; i < m; ++i)
    {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    vector<int> color(2 * n + 1, -1);
    queue<int> q;
    vector<vector<int>> components[2];
    for (int i = 1; i <= 2 * n; ++i)
      if (color[i] == -1)
      {
        components[0].emplace_back();
        components[1].emplace_back();
        q.push(i);
        color[i] = 0;
        components[0].back().push_back(i);
        while (!q.empty())
        {
          auto x = q.front();
          q.pop();
          for (auto y : adj[x])
            if (color[y] == -1)
            {
              color[y] = 1 - color[x];
              components[color[y]].back().push_back(y);
              q.push(y);
            }
            else
            {
              if (color[y] != 1 - color[x])
              {
                cout << "IMPOSSIBLE";
                return 0;
              }
            }
        }
      }
/*
    for (size_t i = 0; i < components[0].size(); ++i)
    {
      for (int j = 0; j < 2; ++j)
      {
        for (auto x : components[j][i])
          cout << x << " ";
        cout << " || ";
      }
      cout << endl;
    }
*/
    vector<vector<int>> dp;
    dp.resize(components[0].size(), vector<int>(2 * n + 1, -1));
    dp[0][components[0][0].size()] = 0;
    dp[0][components[1][0].size()] = 1;

    for (int i = 1; i < components[0].size(); ++i)
    {
      for (size_t j = 1; j <= 2 * n; ++j)
        if (dp[i - 1][j] != -1)
        {
          int c0 = components[0][i].size();
          int c1 = components[1][i].size();
          dp[i][j + c0] = 0;
          dp[i][j + c1] = 1;
        }
    }
/*
    cout << components[0].size() << endl;
    for (size_t i = 1; i <= 2 * n; ++i)
      cout << dp.back()[i] << " ";
    cout << endl;
*/
    if (dp[components[0].size() -1][n] == -1)
    {
      cout << "IMPOSSIBLE" << endl;
      return 0;
    }
    std::vector<int> res;
    int s = n;
    for (int i = components[0].size() - 1; i >= 0; --i)
    {
      res.push_back(dp[i][s]);
      s -= components[dp[i][s]][i].size();
    }
    assert(s == 0);
    reverse(res.begin(), res.end());
    for (size_t i = 0; i < res.size(); ++i)
    {
      for (auto x : components[res[i]][i])
        cout << x << " ";
      res[i] = 1 - res[i];
    }
    cout << endl;
    for (size_t i = 0; i < res.size(); ++i)
    {
      for (auto x : components[res[i]][i])
        cout << x << " ";
    }
    return 0;
}
