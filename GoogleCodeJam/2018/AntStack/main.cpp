#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
      int n;
      cin >> n;
      vector<int> w(n);
      for (int i = 0; i < n; ++i)
        cin >> w[i];
      vector<int64_t> res(1, 0);
      for (int i = 0; i < n; ++i)
      {
        res.push_back(-1);
        for (int j = res.size() - 1; j > 0; --j)
        {
          if (res[j - 1] <= 6 * w[i] && res[j - 1] != -1 &&
              (res[j] == -1 || res[j] > res[j - 1] + w[i]))
          {
            res[j] = (res[j - 1] == - 1 ? 0 : res[j - 1]) + w[i];
          }
        }
        while (res.back() == -1)
          res.pop_back();
//        for (auto x : res)
//          cout << x << " ";
//        cout << endl;
      }
      cout << "Case #" << o + 1 << ": ";
      for (int i = res.size() - 1; i > 0; --i)
        if (res[i] != -1)
      {
        cout << i;
        break;
      }
      cout << endl;
    }
    return 0;
}
