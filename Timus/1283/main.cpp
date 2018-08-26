#include <iostream>

using namespace std;

int main()
{
    int n, r, p;
    cin >> n >> r >> p;
    int y = 0;
    double m = 1.0 - p / 100.0;
    double rem = n;
    while (rem > r)
    {
      y++;
      rem *= m;
    }
    cout << y << endl;
    return 0;
}
