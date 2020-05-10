#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int x, y;
        cin >> x >> y;
        string s;
        cin >> s;
        int turn = 0;
        int res = -1;
        for (auto d : s)
        {
            ++turn;
            switch (d)
            {
            case 'W':
                x -= 1;
                break;
            case 'E':
                x += 1;
                break;
            case 'N':
                y += 1;
                break;
            case 'S':
                y -= 1;
                break;
            }
            int dist = abs(x) + abs(y);
            if (dist <= turn)
            {
                res = turn;
                break;
            }
        }
        cout << "Case #" << o + 1 << ": ";
        if (res == -1)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << res << endl;
    }
    return 0;
}
