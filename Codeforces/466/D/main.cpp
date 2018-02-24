#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    string b;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cin >> b;
    int l = -1000 * 1000 * 1000;
    int r = 1000 * 1000 * 1000;
    for (int i = 4; i < b.size(); ++i)
    {
        if (b[i - 1] == '0' && b[i - 2] == '0' &&
            b[i - 3] == '0' && b[i - 4] == '0' && b[i] == '1')
        {
            int m = a[i];
            for (int j = 1; j <= 4; ++j)
                if (a[i - j] > m)
                    m = a[i - j];
            if (m + 1 > l)
                l = m + 1;
            continue;
        }
        if (b[i - 1] == '1' && b[i - 2] == '1' &&
            b[i - 3] == '1' && b[i - 4] == '1' && b[i] == '0')
        {
            int m = a[i];
            for (int j = 1; j <= 4; ++j)
                if (a[i - j] < m)
                    m = a[i - j];
            if (r > m - 1)
                r = m - 1;
        }
    }
    cout << l << " " << r;
    return 0;
}
