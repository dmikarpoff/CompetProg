#include <iostream>
#include <vector>

using namespace std;

const int offset[4][2] = {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
const int corner[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

int main()
{
    int h, w;
    vector<vector<int>> city;
    vector<vector<int>> res;
    cin >> h >> w;
    city.resize(h, vector<int>(w));
    res.resize(h, vector<int>(w));
    for (int i = 0; i < h; ++i)
      for (int j = 0; j < w; ++j)
        cin >> city[i][j];
    for (int i = 0; i < h; ++i)
      for (int j = 0; j < w; ++j)
      {
        if (city[i][j] != 0)
        {
          res[i][j] = -1;
          continue;
        }
        int local_res = 0;
//        cout << "Next pt " << i << " " << j << endl;
        for (int d = 1; d <= 5 && local_res == 0; ++d)
        {
//          cout << "d = " << d << endl;
          int x = i + corner[3][0] * d, y = j + corner[3][1] * d;
          for (int t = 0; t < 4; ++t)
          {
              int xd = i + corner[t][0] * d;
              int yd = j + corner[t][1] * d;
              while (x != xd || y != yd)
              {
                if (x >= 0 && x < h && y >= 0 && y < w)
                {
//                  cout << x << " " << y << endl;
                    local_res |= city[x][y];
                }
                x += offset[t][0];
                y += offset[t][1];
              }
          }
        }
        res[i][j] = local_res;
      }

    for (int i = 0; i < h; ++i)
    {
      for (int j = 0; j < w; ++j)
        cout << res[i][j] << " ";
      cout << endl;
    }
    return 0;
}
