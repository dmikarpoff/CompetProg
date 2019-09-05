#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int y = 0, z = 0;
    int x1 = 0, y1 = 0;
    int x2 = 0, z2 = 0;
    for (int i = 0; i < n; ++i)
    {
      char c;
      int t;
      cin >> c >> t;
      switch (c)
      {
      case 'X':
        y += t;
        z -= t;
        x1 += t;
        x2 += t;
        break;
      case 'Y':
        y += t;
        y1 += t;
        x2 += t;
        z2 += t;
        break;
      case 'Z':
        z += t;
        y1 += t;
        x1 -= t;
        z2 += t;
        break;
      default:
        return -1;
      }
    }
//    cout << y << " " << z << endl;
//    cout << x1 << " " << y1 << endl;
//    cout << x2 << " " << z2 << endl;
    if (y == 0 && z == 0)
    {
      cout << "0";
      return 0;
    }
    if (y == 0)
    {
      cout << "1\nZ " << -z;
      return 0;
    }
    if (z == 0)
    {
      cout << "1\nY " << -y;
      return 0;
    }
    if (y1 == 0)
    {
      cout << "1\nX " << -x1;
      return 0;
    }
    if (y * z > 0)
    {
      cout << "2\nY " << -y << "\nZ " << -z;
      return 0;
    }
    if (x1 * y1 > 0)
    {
      cout << "2\nX " << -x1 << "\nY " << -y1;
      return 0;
    }
    if (x2 * z2 < 0)
    {
      cout << "2\nX " << -x2 << "\nZ " << -z2;
      return 0;
    }
    return -1;
}
