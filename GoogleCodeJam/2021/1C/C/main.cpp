#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

constexpr int kDpBound = 10000;
int dp[kDpBound][kDpBound];

string to_bin_str(int v)
{
    if (v == 0)
    {
        return "0";
    }
    string res;
    while (v > 0)
    {
        res += v % 2 ? '1' : '0';
        v /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    for (size_t i = 0; i < kDpBound; ++i)
        for (size_t j = 0; j < kDpBound; ++j)
            dp[i][j] = -1;
    vector<pair<int, int>> v;
    for (int i = 0; i < kDpBound; ++i)
    {
        v.push_back(make_pair(i, i));
        dp[i][i] = 0;
    }
    while (!v.empty())
    {
        vector<pair<int, int>> upd_v;
        for (const auto& p : v)
        {
            int x = p.first;
            int y = p.second;
            if (p.first % 2 == 0)
            {
                int z = p.first / 2;
                if (dp[z][y] == -1 || dp[z][y] > dp[x][y] + 1)
                {
                    dp[z][y] = dp[x][y] + 1;
                    upd_v.push_back(make_pair(z, y));
                }
            }
            string bin_x = to_bin_str(x);
            for (size_t i = 0; i < bin_x.size(); ++i)
            {
                bin_x[i] = (bin_x[i] == '0' ? '1' : '0');
            }
            if (bin_x.size() > 1 && bin_x[0] == '0')
            {
                bin_x = '1' + bin_x;
            }
            for (;;)
            {
                int z = stoi(bin_x, nullptr, 2);
                if (z >= kDpBound)
                {
                    break;
                }
                if (dp[z][y] == -1 || dp[z][y] > dp[x][y] + 1)
                {
                    dp[z][y] = dp[x][y] + 1;
                    upd_v.push_back(make_pair(z, y));
                }
                bin_x = '1' + bin_x;
            }
        }
        v = std::move(upd_v);
    }

    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        string s, e;
        cin >> s >> e;
        cout << "Case #" << o + 1 << ": ";
        int res = dp[stoi(s, nullptr, 2)][stoi(e, nullptr, 2)];
        if (res == -1)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            cout << res << endl;
        }
    }
    return 0;
}
