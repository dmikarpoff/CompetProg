#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int n;
        cin >> n;
        vector<int> row(n, 0);
        int sum = 0;
        int rc = 0;
        vector<char> failed_col(n, 0);
        vector<vector<char>> used(n, vector<char>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> row[j];
                auto v = row[j] - 1;
                if (used[j][v] == 1)
                {
                    failed_col[j] = 1;
                }
                used[j][v] = 1;
            }
            sum += row[i];
            sort(row.begin(), row.end());
            for (int j = 1; j < row.size(); ++j)
                if (row[j] == row[j - 1])
                {
                    ++rc;
                    break;
                }
        }
        int cc = accumulate(failed_col.begin(), failed_col.end(), 0);
        cout << "Case #" << o + 1 << ": ";
        cout << sum << " " << rc << " " << cc;
        cout << endl;
    }
    return 0;
}
