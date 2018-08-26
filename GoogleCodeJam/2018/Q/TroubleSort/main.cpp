#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int n;
        cin >> n;
        vector<int> even;
        vector<int> odd;
        even.reserve(n / 2 + 1);
        odd.reserve(n / 2 + 1);
        for (int i = 0; i < n; ++i)
        {
            int val;
            scanf("%d", &val);
            if (i % 2)
                odd.push_back(val);
            else
                even.push_back(val);
        }
        sort(even.begin(), even.end());
        sort(odd.begin(), odd.end());
        cout << "Case #" << o + 1 << ": ";
        bool failed = false;
        for (int i = 0; i < n - 1; ++i)
        {
            if (i % 2)
            {
                if (even[i / 2 + 1] < odd[i / 2])
                {
                    failed = true;
                    cout << i << endl;
                    break;
                }
            }
            else
            {
                if (odd[i / 2] < even[i / 2])
                {
                    failed = true;
                    cout << i << endl;
                    break;
                }
            }
        }
        if (!failed)
            cout << "OK" << endl;
    }
    return 0;
}
