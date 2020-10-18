#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int n, x;
        cin >> n >> x;
        int even = 0;
        int odd = 0;
        for (int i = 0; i < n; ++i)
        {
            int v;
            cin >> v;
            if (v % 2 == 0)
            {
                even++;
            }
            else
            {
                ++odd;
            }
        }
        if (odd == 0)
        {
            cout << "No" << endl;
            continue;
        }
        if (x % 2 == 1)
        {
            --odd;
            --x;
            cout << (even + (odd / 2) * 2 >= x ? "Yes" : "No") << endl;
        }
        else
        {
            if (even == 0)
            {
                cout << "No" << endl;
                continue;
            }
            --odd;
            --even;
            x -= 2;
            cout << (even + (odd / 2) * 2 >= x ? "Yes" : "No") << endl;
        }
    }
    return 0;
}
