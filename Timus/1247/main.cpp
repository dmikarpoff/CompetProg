#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int s, n;
    cin >> s >> n;
    int sum = 0;
    int min_sum = 0;
    for (int i = 0; i < s; ++i)
    {
      int t;
      cin >> t;
      sum += t - 1;
      if (sum - min_sum > n)
      {
//        cout << sum << " " << min_sum << " " << n << endl;
        cout << "NO" << endl;
        return 0;
      }
      if (sum < min_sum)
        min_sum = sum;
    }
    cout << "YES" << endl;
    return 0;
}
