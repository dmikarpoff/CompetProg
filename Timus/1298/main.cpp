#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int> > used;
vector<pair<int, int>> res;
int shift[][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                  {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

int touch(int x, int y) {
  int res = 0;
  for (int j = 0; j < 8; ++j) {
    int x1 = x + shift[j][0];
    int y1 = y + shift[j][1];
    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || used[x1][y1])
      continue;
    ++res;
  }
  return res;
}

bool dfs(int x, int y) {
  res.push_back(make_pair(x, y));
  if (res.size() == n * n)
    return true;
  used[x][y] = true;
  vector<pair<int, int>> next;
  next.reserve(8);
  for (int j = 0; j < 8; ++j) {
    int x1 = x + shift[j][0];
    int y1 = y + shift[j][1];
    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || used[x1][y1])
      continue;
    next.push_back(make_pair(touch(x1, y1), j));
  }
  sort(next.begin(), next.end());
  for (const auto& p : next) {
    int x1 = x + shift[p.second][0];
    int y1 = y + shift[p.second][1];
    if (dfs(x1, y1))
      return true;
  }
  used[x][y] = false;
  res.pop_back();
  return false;
}

int main()
{
    cin >> n;
    used.resize(n, vector<int>(n, 0));
    if (dfs(0, 0)) {
      for (auto p : res) {
        cout << static_cast<char>('a' + p.first);
        cout << static_cast<char>('1' + p.second);
        cout << endl;
      }
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
