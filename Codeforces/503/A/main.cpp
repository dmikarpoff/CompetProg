#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n, h;
    cin >> n >> h;
    int a, b;
    cin >> a >> b;
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
      int t_a, f_a, t_b, f_b;
      cin >> t_a >> f_a >> t_b >> f_b;
      int cost = abs(t_a - t_b);
      if (t_a == t_b || (f_a >= a && f_a <= b) ||
          (f_b >= a && f_b <= b))
      {
        cout << cost + abs(f_a - f_b) << endl;
        continue;
      }
      if (f_a > b)
      {
        cost += f_a - b + abs(f_b - b);
      }
      else
      {
        cost += a - f_a + abs(f_b - a);
      }
      cout << cost << endl;
    }
    return 0;
}
