#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
    uint32_t a, b;
    cin >> a >> b;
    if (a > b)
      swap(a, b);
    uint32_t seg_cost[50] = {0};
    for (int i = 2; i < 33; ++i)
      seg_cost[i] = 2 * seg_cost[i - 1] + i - 1;

    uint32_t cost_a = 0;
    int i = 1;
    while (a > 0)
    {
      if (a % 2)
        cost_a += seg_cost[i];
      a /= 2;
      ++i;
    }
    uint32_t cost_b = 0;
    i = 1;
    while (b > 0)
    {
      if (b % 2)
        cost_b += seg_cost[i];
      b /= 2;
      ++i;
    }

    cout << "cost b = " << cost_b << endl;
    cout << "cost a = " << cost_a << endl;
    cout << cost_b - cost_a;
    return 0;
}
