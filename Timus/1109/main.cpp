#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool toss_up(const vector<vector<int>>& a,
             vector<int>& used, vector<int>& mt,
             int idx)
{
  if (used[idx])
    return false;
  used[idx] = 1;
  for (auto to : a[idx])
  {
//    cout << "trying from " << idx << " to " << to << endl;
    if (mt[to] == -1 || toss_up(a, used, mt, mt[to]))
    {
//      cout << "Setting matching" << endl;
      mt[to] = idx;
      return true;
    }
  }
  return false;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<char> left_used(n + 1, 0);
    vector<char> right_used(m + 1, 0);
    vector<vector<int>> a(n + 1);
    size_t res = 0;
    for (int i = 0; i < k; ++i)
    {
      int f, t;
      cin >> f >> t;
      a[f].push_back(t);
    }

    vector<int> mt(m + 1, -1);
    for (int i = 1; i <= n; ++i)
    {
      vector<int> used(n + 1, 0);
      toss_up(a, used, mt, i);
    }

    size_t matches = 0;
    for (size_t i = 1; i < mt.size(); ++i)
      if (mt[i] != -1)
        matches++;
//    cout << "matches = " << matches << endl;
    cout << n + m - matches << endl;
    return 0;
}
