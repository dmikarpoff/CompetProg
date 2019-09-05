#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> cost(1, 0);
    for (int i = 0; i < n; ++i)
    {
      int k;
      cin >> k;
      string s;
      getline(cin, s);
      vector<int> upd_cost(k, numeric_limits<int>::max());
      for (int j = 0; j < k; ++j)
      {
        getline(cin, s);
        stringstream ss(s);
        int from = 0;
        ss >> from;
        while (from != 0)
        {
          int c;
          ss >> c;
          if (cost[from - 1] != numeric_limits<int>::max() &&
              cost[from - 1] + c < upd_cost[j])
            upd_cost[j] = cost[from - 1] + c;
          ss >> from;
        }
      }
      if (i != n - 1)
        getline(cin, s);
      swap(cost, upd_cost);
    }
    auto res = cost[0];
    for (auto x : cost)
      if (x < res)
        res = x;
    cout << res;
    return 0;
}
