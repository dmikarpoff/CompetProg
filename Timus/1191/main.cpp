#include <iostream>

using namespace std;

int main()
{
    int l, n;
    cin >> l >> n;
    for (int i = 0; i < n; ++i)
    {
      int x;
      cin >> x;
      if (x > l)
      {
        cout << "YES";
        return 0;
      }
      l = (l / x) * x;
    }
    cout << "NO";
    return 0;
}
