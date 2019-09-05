#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> ch(n + 1);
    vector<vector<int>> p(n + 1);
    vector<int> susp(n + 1, 1);
    string s;
    getline(cin, s);
    for (;;)
    {
      getline(cin, s);
      if (s == "BLOOD")
        break;
      int a, b;
      sscanf(s.c_str(), "%d%d", &a, &b);
      ch[b].push_back(a);
      p[a].push_back(b);
    }
    int t;
    while (cin >> t)
    {
      queue<int> q;
      q.push(t);
      susp[t] = 0;
      while (!q.empty())
      {
        int c = q.front();
        q.pop();
        for (auto v : ch[c])
          if (susp[v])
          {
            susp[v] = 0;
            q.push(v);
          }
      }
      q.push(t);
      while (!q.empty())
      {
        int c = q.front();
        q.pop();
        for (auto v : p[c])
          if (susp[v])
        {
          susp[v] = 0;
          q.push(v);
        }
      }
    }
    bool has_res = false;
    for (size_t i = 1; i <= n; ++i)
      if (susp[i] == 1)
      {
        cout << i << " ";
        has_res = true;
      }
    if (!has_res)
      cout << 0;
    return 0;
}
