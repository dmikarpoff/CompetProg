#include <iostream>
#include <vector>

using namespace std;

struct IndexedVal
{
    IndexedVal(int i, double r, double f) : idx(i), rate(r), fine(f) {}
    IndexedVal() = default;

    int idx = 0;
    double rate = 0.0;
    double fine = 0.0;
};

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    double v;
    cin >> v;
    vector<vector<IndexedVal>> rate(n + 1);
    for (auto i = 0; i < m; ++i)
    {
        int a, b;
        double rab, cab, rba, cba;
        cin >> a >> b >> rab >> cab >> rba >> cba;
        rate[a].emplace_back(b, rab, cab);
        rate[b].emplace_back(a, rba, cba);
    }
    vector<double> max_sum(n + 1, -1.0);
    max_sum[s] = v;
    for (int i = 0; i <= n; ++i)
    {
        vector<double> next_sum = max_sum;
        bool increased  = false;
        for (int j = 1; j <= n; ++j)
        {
            if (max_sum[j] > -1E-9)
            {
                for (const auto& ival : rate[j])
                {
                    double val = (max_sum[j] - ival.fine) * ival.rate;
                    if (val > -1E-9 && val > next_sum[ival.idx] + 1E-9)
                    {
                        increased = true;
                        next_sum[ival.idx] = val;
                    }
                }
            }
        }
        if (i == n)
        {
            cout << (increased ? "YES" : "NO") << endl;
            return 0;
        }
        swap(next_sum, max_sum);
    }
    return 0;
}
