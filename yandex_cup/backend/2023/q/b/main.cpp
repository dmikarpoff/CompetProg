#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    getline(cin, s);
    int yandex_cost[7];
    int cup_cost[4];
    fill(begin(yandex_cost), end(yandex_cost), -1);
    fill(begin(cup_cost), end(cup_cost), -1);
    const char* y = "Yandex";
    const char* c = "Cup";
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (i + 6 <= s.size())
        {
            int cost = 0;
            for (int j = 0; j < 6; ++j)
            {
                if (s[i + j] != y[j])
                    ++cost;
            }
            if (yandex_cost[cost] == -1)
                yandex_cost[cost] = i;
        }
        if (i + 3 <= s.size())
        {
            int cost = 0;
            for (int j = 0; j < 3; ++j)
            {
                if (s[i + j] != c[j])
                    ++cost;
            }
            cup_cost[cost] = i;
        }
    }

    /*
    for (int i = 0; i < 7; ++i)
        cout << yandex_cost[i] << " ";
    cout << endl;
    for (int i = 0; i < 4; ++i)
        cout << cup_cost[i] << " ";
    cout << endl;
    */

    int res = 100;
    int y_rep = -1;
    int c_rep = -1;
    for (int i = 0; i <= 6; ++i)
    {
        for (int j = 0; j <= 3; ++j)
        {
            if (yandex_cost[i] != -1 && cup_cost[j] != -1 && yandex_cost[i] + 6 <= cup_cost[j] && i + j < res)
            {
                res = i + j;
                y_rep = yandex_cost[i];
                c_rep = cup_cost[j];
            }

        }
    }
    // cout << res << endl;
    // cout << y_rep << " " << c_rep << endl;
    for (int i = 0; i < 6; ++i)
    {
        s[y_rep + i] = y[i];
    }
    for (int i = 0; i < 3; ++i)
    {
        s[c_rep + i] = c[i];
    }
    cout << s << endl;
    return 0;
}
