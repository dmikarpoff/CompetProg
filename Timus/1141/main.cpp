#include <cassert>
#include <iostream>

using namespace std;

int power(int b, int p, int mod)
{
  int res = 1;
  int mult = b;
  while (p > 0)
  {
    if (p & 1)
      res = (res * mult) % mod;
    p >>= 1;
    mult = (mult * mult) % mod;
  }
  return res;
}

int main()
{
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
      int e, n, c;
      cin >> e >> n >> c;
      int p = 3;
      for (; p * p < n; ++p)
        if (n % p == 0)
          break;
      int q = n / p;
      int phi = (p - 1) * (q - 1);
      int copy_phi = phi;
      int phi_phi = phi;
      for (size_t i = 2; i <= copy_phi; ++i)
      {
        if (copy_phi % i == 0)
        {
          while (copy_phi % i == 0)
            copy_phi /= i;
          phi_phi = phi_phi * (i - 1) / i;
        }
      }
      int rev = power(e, phi_phi - 1, phi);
      assert(rev * e % phi == 1);
      cout << power(c, rev, n) << endl;
    }
    return 0;
}
