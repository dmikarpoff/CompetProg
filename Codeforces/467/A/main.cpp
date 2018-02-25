#include <iostream>

using namespace std;

int a[605];

int main()
{
    int n, val;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> val;
        a[val]++;
    }
    int cnt = 0;
    for (int i = 1; i <= 600; ++i)
        if (a[i])
            ++cnt;
    cout << cnt;
    return 0;
}
