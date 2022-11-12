#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    std::ifstream in("C:\\my_devel\\CompetProg\\yandex_cup\\analytics\\2022\\q\\dataset\\dataset.tsv");
    double data[15][2][1500];
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 2; ++j)
            for (int h = 0; h < 1500; ++h)
                data[i][j][h] = 0.0;
    int n;
    while (in >> n)
    {
        int t, id;
        double val;
        in >> t >> id >> val;
        data[n - 1][t - 1][id] = val;
    }
    double e[1500], sigma[1500], sigma2[2][1500];
    for (int i = 0; i < 1500; ++i)
    {
        e[i] = 0.0;
        sigma[i] = 0.0;
    }
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 2; ++j)
            for (int h = 0; h < 1500; ++h)
            {
                e[h] += data[i][j][h] / 30.0;
            }
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 1500; ++j)
            sigma2[i][j] = 0.0;

    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 2; ++j)
            for (int h = 0; h < 1500; ++h)
            {
                double s = data[i][j][h] - e[h];
                sigma[h] += s * s / 30.0;
            }

    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 2; ++j)
            for (int h = 0; h < 1500; ++h)
            {
                double s = (data[i][j][h] - e[h]) / sqrt(sigma[h]);
                sigma2[j][h] += abs(s) / 15.0;
            }
    std::vector<std::pair<double, int>> res;
    for (int i = 0; i < 1500; ++i)
        res.push_back(make_pair(abs(sigma2[0][i] - sigma2[1][i]), i));
    sort(res.rbegin(), res.rend());
    for (int i = 0; i < 20; ++i)
    {
        cout << res[i].second << "->" << res[i].first << endl;
    }
    return 0;
}
