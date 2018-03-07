#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    if (b < a)
        swap(a, b);
    int mid = (a + b) / 2;
    int da = mid - a;
    uint32_t res = (da + 1) * da;
    if (mid * 2 != a + b)
        res += da + 1;
    cout << res;
    return 0;
}
