#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int n;
        cin >> n;
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            int v;
            cin >> v;
            if (v != i)
            {
                ++cnt;
            }
        }
        printf("Case #%d: %.6f\n", o + 1, static_cast<float>(cnt));
    }
    return 0;
}
