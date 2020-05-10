#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 1; o <= T; ++o)
    {
        int n, k;
        cin >> n >> k;
        vector<int> trace;
        int x = 1;
        for (int i = 2; i * i <= k; ++i)
        {
            if (k % i == 0)
            {
                x = i;
            }
        }
        int y = k / x;
        // cout << "x = " << x << endl;
        // cout << "y = " << y << endl;
        if (x > n || y > n || x == 1)
        {
            cout << "Case #" << o << ": ";
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        vector<int> line(n);
        line[0] = 1;
        line[1] = x;
        line[n - 1] = y;
        for (int i = 2, v = 2; i < n - 1;)
        {
            if (v != x && v != y)
            {
                line[i] = v;
                ++i;
            }
            ++v;
        }
        cout << "Case #" << o << ": ";
        cout << "POSSIBLE" << endl;
        for (int i = 0; i < n; ++i)
        {
            int offset = (i < 2 ? 1 - i : i);
            for (int j = 0; j < n; ++j)
                cout << line[(j + n - offset) % n] << " ";
            cout << endl;
        }
    }
    return 0;
}

/*
x 1 y 2 3 4
1 y 2 3 4 x
    1 y
       1
         1






*/
