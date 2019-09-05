#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<string>> teams(n, vector<string>(3, ""));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < 3; ++j)
        cin >> teams[i][j];

    vector<vector<int>> incompat(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
      {
        for (const auto& s : teams[i])
          if (find(teams[j].begin(), teams[j].end(), s) != teams[j].end())
          {
            incompat[i][j] = 1;
            incompat[j][i] = 1;
          }
      }
/*
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < n; ++j)
        cout << incompat[i][j];
      cout << endl;
    }
*/
    int res = 0;
    for (int i = 0; i < (1 << n); ++i)
    {
      int x = i;
      vector<int> t;
      for (int j = 0; j < n; ++j)
        if (x & (1 << j))
          t.push_back(j);

      bool compatible = true;
      for (size_t j = 0; j < t.size() && compatible; ++j)
        for (size_t h = j + 1; h < t.size() && compatible; ++h)
          if (incompat[t[j]][t[h]])
            compatible = false;

      if (compatible && res < t.size())
        res = t.size();
    }
    cout << res << endl;
    return 0;
}
