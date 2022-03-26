#include <iostream>

using namespace std;

int main()
{
    uint64_t n, m;
    cin >> n >> m;
    uint64_t res = n * m;
    // cout << res << endl;
    if (m >= n && m > 1)
    {
        int ls = n / 2;
        while (m >= n && m > 1)
        {
            res += n - ls;
            m /= 2;
            ls /= 2;
            // cout << res << endl;
        }
    } else if (m < n && n > 1)
    {
        int ls = m / 2;
        while (m < n && n > 1)
        {
            res += m - ls / 2;
            n /= 2;
            ls /= 2;
        }
    }

    // cout << n << " " << m << endl;

    while (m > 1)
    {
        ++res;
        m /= 2;
    }
    while (n > 1)
    {
        ++res;
        n /= 2;
    }

    cout << res;
    return 0;
}
