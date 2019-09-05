#include <iostream>
#include <algorithm>

using namespace std;

int estimate(int n, int k) {
  if (n < k)
    return 0;
  if (n % k == 0)
    return n * n / k;
  return max((n / k) * n + (n / k) * (n % k),
             estimate(n - 2 * (n % k), k) + 4 * (n % k) * (n / k));
}

int main()
{
    int n, k;
    cin >> n >> k;
    cout << estimate(n, k) << endl;
    return 0;
}
