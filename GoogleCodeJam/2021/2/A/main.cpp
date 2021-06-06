#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

int main()
{
    int t, n;
    cin >> t >> n;
    for (int o = 0; o < t; ++o)
    {
        for (int i = 0; i < n - 1; ++i)
        {
            cout << "M " << i + 1 << " " << n << endl;
            int p;
            cin >> p;
            if (p != i + 1)
            {
                cout << "S " << min(p, i + 1) << " " << max(p, i + 1) << endl;
                int x;
                cin >> x;
                assert(x == 1);
            }
        }
        cout << "D" << endl;
        int x;
        cin >> x;
        assert(x == 1);
    }
    return 0;
}
