#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int64_t x, y;
        cin >> x >> y;
        string res;
        int64_t cur_x = 0, cur_y = 0;
        bool impossible = false;
        int64_t abs_x = abs(x);
        int64_t abs_y = abs(y);
        for (uint64_t pw = 1; abs_x != abs(cur_x) || abs_y != abs(cur_y); pw *= 2)
        {
            /*
            cout << "Res = " << res << endl;
            cout << "cur_x = " << cur_x << endl;
            cout << "cur_y = " << cur_y << endl;
            cout << "pw = " << pw << endl;
            */
            int64_t r_x = abs(abs_x - cur_x) / pw;
            int64_t r_y = abs(abs_y - cur_y) / pw;
            if (r_x % 2 == 1 && r_y % 2 == 0)
            {
                cur_x += pw;
                res += 'E';
                continue;
            }
            if (r_x % 2 == 0 && r_y % 2 == 1)
            {
                cur_y += pw;
                res += 'N';
                continue;
            }
            if (res.empty())
            {
                impossible = true;
                break;
            }
            if (res.back() == 'N')
            {
                res.back() = 'S';
                cur_y -= pw;
                pw /= 2;
                continue;
            }
            if (res.back() == 'E')
            {
                res.back() = 'W';
                cur_x -= pw;
                pw /= 2;
                continue;
            }
            if (res.back() == 'W' || res.back() == 'S')
            {
                impossible = true;
                break;
            }
        }
        cout << "Case #" << o + 1 << ": ";
        if (impossible)
        {
            cout << "IMPOSSIBLE";
        }
        else
        {
            if (abs_x != x)
            {
                for (size_t i = 0; i < res.size(); ++i) {
                    if (res[i] == 'E')
                        res[i] = 'W';
                    else if (res[i] == 'W')
                        res[i] = 'E';
                }
            }
            if (abs_y != y)
            {
                for (size_t i = 0; i < res.size(); ++i)
                {
                    if (res[i] == 'N')
                        res[i] = 'S';
                    else if (res[i] == 'S')
                        res[i] = 'N';
                }
            }
            cout << res;
        }
        cout << endl;
    }
    return 0;
}
