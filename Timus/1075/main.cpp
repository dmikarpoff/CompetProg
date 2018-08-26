#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

struct point {
    long long x, y, z;
    long long abs() const {
        return x * x + y * y + z * z;
    }
};

int main()
{
    point a, b, c;
    int r;
    cin >> a.x >> a.y >> a.z;
    cin >> b.x >> b.y >> b.z;
    cin >> c.x >> c.y >> c.z;
    cin >> r;
    a.x -= c.x;
    a.y -= c.y;
    a.z -= c.z;
    b.x -= c.x;
    b.y -= c.y;
    b.z -= c.z;
    point v;
    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;
    long long ds = v.abs();
//    cout << "ds = " << ds << endl;
    point dif;
    dif.x = b.x - a.x;
    dif.y = b.y - a.y;
    dif.z = b.z - a.z;
    long long base = dif.abs();
//    cout << "base = " << base << endl;

    if (base == 0) {
        cout << "0.00";
        return 0;
    }
//    cout << "rh_param = " << rh_param << endl;
    long double la = a.abs();
    long double lb = b.abs();
//    cout << "la = " << la << endl;
//    cout << "lb = " << lb << endl;
    if (ds == 0)
    {
      if (a.x * b.x > 0 || a.y * b.y > 0 || a.z * b.z > 0)
      {
        printf("%.2f", sqrt(static_cast<double>(base)));
        return 0;
      }
    }
    else
    {
//      cout << "Sqr ds = " << ds << endl;
      double h = sqrt(ds) / sqrt(static_cast<double>(base));
      long long a_param = -a.x * (b.x - a.x) - a.y * (b.y - a.y) -
                           a.z * (b.z - a.z);
      long long b_param = -b.x * (a.x - b.x) - b.y * (a.y - b.y) -
                           b.z * (a.z - b.z);
//      cout << "a_p = " << a_param << endl;
//      cout << "b_p = " << b_param << endl;
//      cout << "h = " << h << endl;
      if (a_param >= 0 && b_param >= 0)
      {
//        cout << "ds = " << sqrt(ds) / 2.0 << endl;
//        cout << "base = " << base << endl;
        if (ds >= base * r * r)
        {
          printf("%.2f", sqrt(static_cast<double>(base)));
          return 0;
        }
      }
      else
      {
          printf("%.2f", sqrt(static_cast<double>(base)));
          return 0;
      }
    }
    double res = 0.0;
    res += sqrt(la - r * r);
    res += sqrt(lb - r * r);

    double total = acos(max<double>((a.x * b.x + a.y * b.y + a.z * b.z) /
                                    (sqrt(la) * sqrt(lb)), -1.0));
    total -= acos(r / sqrt(la)) + acos(r / sqrt(lb));
    assert(total > -1E-6);
    res += r * total;
    printf("%.2f", static_cast<double>(res));
    return 0;
}
