#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    uint64_t n, k, a, b;
    cin >> n >> k >> a >> b;
    uint64_t cost = 0;
    if (k == 1)
    {
        cout << (n - 1) * a;
        return 0;
    }
    while (n != 1)
    {
        if (n < k)
        {
            cost += (n - 1) * a;
            break;
        }
        if (n % k != 0)
        {
            cost += (n % k) * a;
            n -= n % k;
        }
        else
        {
            uint64_t m = n / k;
            if (b < (n - m) * a)
                cost += b;
            else
                cost += (n - m) * a;
            n = m;
        }
    }
    cout << cost << endl;
    return 0;
}
