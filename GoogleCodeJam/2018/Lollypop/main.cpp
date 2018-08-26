#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
      int n;
      cin >> n;
      vector<int> used(n, 0);
      vector<int> liked(n, 0);
      vector<int> last_liked(n, -1);
      for (int i = 0; i < n; ++i)
      {
        int d;
        cin >> d;
        vector<int> cur(d);
        for (int i = 0; i < d; ++i)
          cin >> cur[i];
        for (auto x : cur)
        {
          liked[x]++;
          last_liked[x] = i;
        }
        vector<double> p(n);
        for (int j = 0; j < n; ++j)
        {
          p[j] = static_cast<double>(liked[j]) / (i + 1);
          p[j] = min(max(p[j], 0.005), 0.1);
          p[j] = pow(1 - p[j], min<double>((n - last_liked[j]), 10));
        }
        double m = -1.0;
        int res = -1;
        for (auto x : cur)
        {
          if (!used[x] && p[x] > m)
          {
            m = p[x];
            res = x;
          }
        }
        if (res != -1)
          used[res] = 1;
        cout << res << endl;
      }
    }
    return 0;
}
