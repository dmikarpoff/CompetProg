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
        int a;
        cin >> a;
        int width = 1, height = 1;
        for (int i = 1; i * i < a; ++i)
            if (a % i == 0)
            {
                width = i;
                height = a / i;
            }
        width = max(width, 3);
        height = max(height, 3);
        vector<vector<int> > sum(width, vector<int>(height, 0));
        vector<vector<int> > fld(width, vector<int>(height, 0));
        int x, y;
//        cout << "Case #" << o + 1 << ": ";
        do
        {
            int min_val = 10;
            int best_i = 1, best_j = 1;
            for (int i = 1; i < width - 1; ++i)
                for (int j = 1; j < height - 1; ++j)
            {
                if (sum[i][j] < min_val)
                {
                    min_val = sum[i][j];
                    best_i = i;
                    best_j = j;
                }
            }
            cout << best_i + 1 << " " << best_j + 1 << endl;
            cin >> x >> y;
            if (x == -1 && y == -1)
                return -1;
            if (x == 0 && y == 0)
                break;
            --x;
            --y;
            if (fld[x][y] == 1)
                continue;
            fld[x][y] = 1;
            for (int i = -1; i <= 1; ++i)
                for (int j = -1; j <= 1; ++j)
            {
                int xx = x + i;
                int yy = y + j;
                if (xx < 0 || xx >= width ||
                        yy < 0 || yy >= height)
                    continue;
                sum[xx][yy]++;
            }
        }
        while (true);
    }
    return 0;
}
