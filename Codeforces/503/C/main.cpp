#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct IdxVal
{
  int idx, val;
};

bool operator<(const IdxVal& lhs, const IdxVal& rhs)
{
  return lhs.val < rhs.val || (lhs.val == rhs.val && lhs.idx < rhs.idx);
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cost(m + 1);
    multiset<IdxVal> w;
    for (int i = 0; i < n; ++i)
    {
      int p, c;
      cin >> p >> c;
      cost[p].push_back(c);
      if (p != 1)
        w.insert(IdxVal{p, c});
    }
    if (m == 1)
    {
      cout << 0;
      return 0;
    }

    for (int i = 1; i <= m; ++i)
      sort(cost[i].begin(), cost[i].end(), greater<int>());

    int total_cost = 0;
    while (true)
    {
      int m_idx = 2;
      for (int i = 2; i <= m; ++i)
        if (cost[i].size() > cost[m_idx].size())
          m_idx = i;
      int max_sz = cost[m_idx].size();
      if (cost[1].size() > max_sz)
      {
        cout << total_cost << endl;
        return 0;
      }
      if (cost[1].size() == max_sz)
      {
        cout << total_cost + w.begin()->val;
        return 0;
      }
      int min_cost = w.begin()->val + (w.begin() + 1)->val;
      int another_cost = 0;
      for (size_t i = 2; i < cost.size(); ++i)
        if (cost[i].size() == max_sz && cost[i].back() < min_cost)
        {
          min_cost = i;

        }
    }
    return 0;
}
