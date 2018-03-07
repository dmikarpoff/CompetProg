#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> dst(n + 1, -1);
    vector<int> p(n + 1, -1);
    vector<int> e(n + 1, 0);
    for (int i = 2; i <= n; ++i)
        cin >> p[i];
    dst[1] = 0;
    e[0]  = 1;
    for (int i = 2; i <= n; ++i)
    {
        dst[i] = dst[p[i]] + 1;
        ++e[dst[i]];
    }
    int res = 0;
    for (int i = 0; i < n; ++i)
        if (e[i] % 2 == 1)
            ++res;
    cout << res;
    return 0;
}
