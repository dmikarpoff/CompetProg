#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double n, m;
    cin >> n >> m;
    int i = 0;
    while (m / (2 * i + 1) < n)
    {
      n -= m / (2 * i + 1);
      ++i;
    }
//    cout << "n = " << n << endl;
//    cout << "i = " << i << endl;
    double res = m * i + n * (2 * i + 1);
    cout << static_cast<uint64_t>(std::ceil(res) + 0.1) << endl;
    return 0;
}
