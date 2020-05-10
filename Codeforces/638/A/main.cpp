#include <iostream>
#include <cmath>

using namespace std;

int64_t pw(int p) {
    int64_t res = 1;
    for (int i = 0; i < p; ++i)
        res *= 2;
    return res;
}

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int n;
        cin >> n;
        int64_t a = pw(n);
        for (int i = 1; i < n / 2; ++i)
            a += pw(i);
        int64_t b = 0;
        for (int i = n / 2; i < n; ++i)
            b += pw(i);
        cout << abs(a - b) << endl;
    }
    return 0;
}
