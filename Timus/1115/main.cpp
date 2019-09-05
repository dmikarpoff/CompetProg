#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> ship;
vector<pair<int, int>> row;
vector<char> used;
vector<int> sum;
vector<pair<vector<int>, int> > res;

bool lookup(int idx, int from) {
  if (idx == row.size())
    return true;
  if (sum[idx] == row[idx].first)
    return lookup(idx + 1, 0);
  for (size_t i = from; i < ship.size(); ++i) {
    if (sum[idx] + ship[i] > row[idx].first)
      return false;
    if (used[i])
      continue;
    sum[idx] += ship[i];
    used[i] = true;
    res[idx].first.push_back(ship[i]);
    if (lookup(idx, i + 1))
      return true;
    res[idx].first.pop_back();
    used[i] = false;
    sum[idx] -= ship[i];
  }
  return false;
}

int main()
{
    cin >> n >> m;
    ship.resize(n);
    row.resize(m);
    for (int i = 0; i < n; ++i)
    {
      cin >> ship[i];
    }
    for (int i = 0; i < m; ++i) {
      cin >> row[i].first;
      row[i].second = i;
    }
    sort(ship.begin(), ship.end());
    sort(row.begin(), row.end());
    used.resize(n, false);
    sum.resize(m, 0);
    res.resize(m);
    for (int i = 0; i < m; ++i) {
      res[i] = make_pair(vector<int>(), row[i].second);
    }
    if (!lookup(0, 0))
      cout << "It's a fail" << endl;
    sort(res.begin(), res.end(),
         [](const pair<vector<int>, int>& lhs,
            const pair<vector<int>, int>& rhs) {
            return lhs.second < rhs.second;
         });
    for (auto& line : res) {
      cout << line.first.size() << endl;
      for (auto v : line.first)
        cout << v << " ";
      cout << endl;
    }
    return 0;
}
