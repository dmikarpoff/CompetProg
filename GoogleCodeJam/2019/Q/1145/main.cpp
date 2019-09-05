#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<string> field;
vector<vector<int>> dst;

using pair_ii = pair<int, int>;

int shift[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1} };

void bfs(int x, int y)
{
  dst.clear();
  dst.resize(field.size(), vector<int>(field.front().size(), -1));
  queue<pair_ii> q;
  dst[x][y] = 0;
  q.push(pair_ii(x, y));
  while (!q.empty()) {
    const pair_ii& head = q.front();
    q.pop();
    int d = dst[head.first][head.second];
    for (int i = 0; i < 4; ++i) {
      int x = head.first + shift[i][0];
      int y = head.second + shift[i][1];
      if (x < 0 || y < 0 || x >= field.size() ||
          y >= field.front().size())
        continue;
      if (field[x][y] == '#' || dst[x][y] != -1)
        continue;
      dst[x][y] = d + 1;
      q.push(pair_ii(x, y));
    }
  }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
      string s;
      cin >> s;
      field.emplace_back(move(s));
    }
    bool stop = false;
    for (int i = 0; i < m && !stop; ++i)
      for (int j = 0; j < n && !stop; ++j)
        if (field[i][j] == '.') {
          bfs(i, j);
          stop = true;
        }
    int x = 0, y = 0;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (dst[x][y] < dst[i][j]) {
            x = i;
            y = j;
        }
    bfs(x, y);
    x = 0, y = 0;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (dst[x][y] < dst[i][j]) {
            x = i;
            y = j;
        }
    cout << dst[x][y];
    return 0;
}
