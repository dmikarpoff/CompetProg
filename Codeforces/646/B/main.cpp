#include <iostream>
#include <string>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        string s;
        cin >> s;
        int zero = 0;
        int one = 0;
        for (auto c : s)
        {
            if (c == '0')
            {
                ++zero;
            }
            else
            {
                ++one;
            }
        }
        if (zero == 0 || zero == s.size())
        {
            cout << 0 << endl;
            continue;
        }
        int res = s.size();
        int cur_zero = 0;
        int cur_one = 0;
        for (auto c : s)
        {
            c == '0' ? ++cur_zero : ++cur_one;
            if (cur_one + zero - cur_zero < res)
            {
                res = cur_one + zero - cur_zero;
            }
            if (cur_zero + one - cur_one < res)
            {
                res = cur_zero + one - cur_one;
            }
        }
        cout << res << endl;
    }
    return 0;
}
