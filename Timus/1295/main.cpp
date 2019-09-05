#include <iostream>
#include <cmath>
#include <numeric>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int mod[] = {0, 1, 2, 3, 4};
    for (int i = 1; i < n; ++i)
    {
      for (int j = 1; j <= 4; ++j)
        mod[j] = (mod[j] * j) % 100;
    }
    int sum = std::accumulate(begin(mod), end(mod), 0);
    if (sum % 100 == 0)
      cout << 2;
    else if (sum % 10 == 0)
      cout << 1;
    else
      cout << 0;
    return 0;
}
