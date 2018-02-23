#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

void apply(string (&fld)[4], const string (&mask)[3],
           int i, int j)
{
    for (int di = -1; di <= 1; ++di)
        for (int dj = -1; dj <= 1; ++dj)
        {
            int ui = i + di;
            int uj = j + dj;
            if (ui >= 0 && ui < 4 && uj >= 0 && uj < 4 &&
                mask[di + 1][dj + 1] == '1')
            {
                fld[ui][uj] = (fld[ui][uj] == 'B' ? 'W' : 'B');
            }
        }
}

int main()
{
    string fld[4];
    for (int i = 0; i < 4; ++i)
        cin >> fld[i];
    string mask[3];
    for (int i = 0; i < 3; ++i)
        cin >> mask[i];
    size_t best_cnt = -1;
    for (uint32_t i = 0; i < (1 << 16); ++i)
    {
        string mod_fld[4] = fld;
        size_t cnt = 0;
        for (uint32_t j = 0; j < 16; ++j)
            if ((1 << j) & i)
            {
                apply(mod_fld, mask, j / 4, j % 4);
                cnt++;
            }
        bool unif = true;
        for (size_t j = 0; j < 3; ++j)
            if (mod_fld[0][j] != mod_fld[0][j + 1])
        {
            unif = false;
            break;
        }
        for (size_t j = 0; j < 3; ++j)
            if (mod_fld[j] != mod_fld[j + 1])
            {
                unif = false;
                break;
            }
        if (unif && cnt < best_cnt)
            best_cnt = cnt;
    }
    if (best_cnt == static_cast<size_t>(-1))
        cout << "Impossible";
    else
        cout << best_cnt;
    return 0;
}
