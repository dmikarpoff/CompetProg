#include <iostream>
#include <cassert>
#include <utility>
#include <algorithm>

using namespace std;

pair<int, int> ext_euc(int p, int q)
{
  if (q == 0)
    return make_pair(1, 0);
  auto res = ext_euc(q, p % q);
  return make_pair(res.second, res.first - p / q * res.second);
}

int main()
{
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
      int n;
      cin >> n;
      int p = 2;
      while (p * p <= n)
      {
        if (n % p == 0)
          break;
        ++p;
      }
      int q = n / p;
      auto a = ext_euc(q, p);
      int x = a.first * q;
      if (x < 0)
        x += n;
      int y = a.second * p;
      if (y < 0)
        y += n;
      cout << 0 << " " << 1 << " " << min(x, y)
           << " " << max(x, y) << endl;
    }
    return 0;
}
