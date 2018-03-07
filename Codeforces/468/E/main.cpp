#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> tbl['z' - 'a' + 1];

int main()
{
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); ++i)
    {
        string ts(s.begin() + i, s.end());
        ts += string(s.begin(), s.begin() + i);
        tbl[ts[0] - 'a'].push_back(ts);
    }
    double res = 0.0;
    for (int i = 0; i < 'z' - 'a' + 1; ++i)
    {
        double loc_res = 0.0;
        for (size_t j = 1; j < s.size(); ++j)
        {
            int cnt['z' - 'a' + 1] = {0};
            int succ = 0, fail = 0;
            for (int h = 0; h < tbl[i].size(); ++h)
                cnt[tbl[i][h][j] - 'a']++;
            for (int h = 0; h < 'z' - 'a' + 1; ++h)
                if (cnt[h] == 1)
                    succ++;
            if ((double)succ / tbl[i].size() > loc_res)
                loc_res = (double)succ / tbl[i].size();
        }
        res += loc_res * tbl[i].size();
    }
    cout << res / s.size();
    return 0;
}
