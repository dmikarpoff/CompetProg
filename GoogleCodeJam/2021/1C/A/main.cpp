#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 1; o <= t; ++o)
    {
        int n, k;
        cin >> n >> k;
        vector<int> p(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> p[i];
        }
        sort(p.begin(), p.end());
        vector<int> d;
        for (int i = 1; i < n; ++i)
        {
            if (p[i] > p[i - 1])
            {
                d.push_back(p[i] - p[i - 1]);
            }
        }
        sort(d.begin(), d.end());
        double res = -1.0;
        if (d.size() == 0) {
            res = static_cast<double>(k - 1) / k;
        } else {
            int most_left = p.front() - 1;
            int most_right = k - p.back();
            int double_longest_run = d.back() - 1;
            int longest_run = double_longest_run > 0 ? (double_longest_run - 1) / 2 + 1 : 0;
            int second_run = 0;
            if (d.size() > 1) {
                int x = d[d.size() - 2];
                second_run = x >= 2 ? (x - 2) / 2 + 1 : 0;
            }

            int max_nom = double_longest_run;
            // cout << "double_longest = " << double_longest_run << endl;
            int a[4] = {most_left, most_right, longest_run, second_run};
            for (int i = 0; i < 4; ++i)
            {
                // cout << a[i] << " ";
                for (int j = i + 1; j < 4; ++j)
                    if (a[i] + a[j] > max_nom)
                    {
                        max_nom = a[i] + a[j];
                    }
            }
            // cout << endl;
            res = static_cast<double>(max_nom) / k;
        }
        cout << "Case #" << o << ": ";
        cout << setprecision(7) << fixed << res;
        cout << endl;
    }
    return 0;
}
