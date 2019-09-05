#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct Wire
{
  int u;
  int v;
  int c;
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<Wire> wires;
    for (int i = 0; i < m; ++i)
    {
      Wire w;
      cin >> w.u >> w.v >> w.c;
      wires.push_back(w);
    }
    sort(wires.begin(), wires.end(),
         [](const Wire& lhs, const Wire& rhs)
         {
           return lhs.c < rhs.c;
         });
    vector<vector<int>> comp(n + 1);
    vector<int> num(n + 1);
    for (int i = 1; i <= n; ++i)
    {
      comp[i].push_back(i);
      num[i] = i;
    }
    for (size_t i = 0; i < wires.size(); ++i)
    {
      auto u = wires[i].u;
      auto v = wires[i].v;
//      cout << u << " " << v << endl;
      if (num[u] != num[v])
      {
//        cout << "- " << num[u] << " " << num[v] << endl;
        bool done = false;
//        cout << "  " << comp[num[u]].size() << " " << comp[num[v]].size() << endl;
        if (comp[num[u]].size() < comp[num[v]].size())
        {
          int nu = num[u];
          for (auto x : comp[num[u]])
            num[x] = num[v];
          comp[num[v]].insert(comp[num[v]].end(), comp[nu].begin(),
                              comp[nu].end());
          if (comp[num[v]].size() == n)
            done = true;
        }
        else
        {
          int nv = num[v];
          for (auto x : comp[num[v]])
            num[x] = num[u];
          comp[num[u]].insert(comp[num[u]].end(), comp[nv].begin(),
                              comp[nv].end());
          if (comp[num[u]].size() == n)
          {
            done = true;
//            for (auto x : num)
//              cout << x << " ";
//            cout << endl;
          }
        }
        if (done)
        {
          cout << wires[i].c << endl;
          cout << i + 1 << endl;
          for (int j = 0; j <= i; ++j)
          {
            cout << wires[j].u << " " << wires[j].v << endl;
          }
          return 0;
        }
      }
//      for (auto x : num)
//        cout << x << " ";
//      cout << endl;
    }
    assert(false);
    return 0;
}
