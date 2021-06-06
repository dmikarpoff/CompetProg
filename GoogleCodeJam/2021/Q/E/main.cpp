#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    int t, p;
    cin >> t >> p;
    for (int o = 0; o < t; ++o) {
        string player[100];
        std::vector<int> d(10000, 0);
        vector<int> p(100, 0);
        for (int i = 0; i < 100; ++i) {
            cin >> player[i];
            for (size_t j = 0; j < player[i].size(); ++j)
                if (player[i][j] == '1') {
                    ++d[j];
                    ++p[i];
                }
        }
        vector<double> task_rate(10000, 0.0);
        //cout << "\n\nTasks: " << endl;
        for (size_t i = 0; i < 10000; ++i) {
            task_rate[i] = d[i] < 1e-3 ? 3.0 : log(100.0 / d[i] - 1.0);
            //cout << i << ": " << task_rate[i] << " " << d[i] << endl;
        }
        vector<double> task_rate_copy{task_rate};
        sort(task_rate_copy.begin(), task_rate_copy.end());
        double left_bound = task_rate_copy[task_rate.size() / 20];
        double right_bound = task_rate_copy[18 * task_rate.size() / 20];
        //cout << "\n\nPlayers: " << endl;
        vector<double> player_rate(100, 0.0);
        for (size_t i = 0; i < 100; ++i) {
            player_rate[i] = p[i] < 1e-7 ? -3.0 : -log(10000.0 / p[i] - 1.0);
            //cout << i << ": " << player_rate[i] << " " << p[i] << endl;
        }
        double max_cost = -1e+100;
        int idx = 0;
        //cout << "right_bound = " << right_bound << std::endl;
        for (int i = 0; i < 100; ++i) {
            double expected_low = 0.0;
            double expected_high = 0.0;
            double actual_low = 0;
            double actual_high = 0;
            for (size_t j = 0; j < player[i].size(); ++j) {
                double p_ans = 1.0 / (1.0 + exp(task_rate[j] - player_rate[i]));
                /*
                if (task_rate[j] < left_bound) {
                    expected_low += p_ans;
                    if (player[i][j] == '1') {
                        actual_low += 1.0;
                    }
                } else*/
                if (task_rate[j] >= right_bound) {
                    expected_high += p_ans;
                    if (player[i][j] == '1') {
                        actual_high += 1.0;
                    }
                }
            }
            //cout << "Player " << i  << " with rate " << player_rate[i] << ": expected " << expected_high << " actual " << actual_high << endl;
            double cost = actual_high - expected_high;
            if (cost > max_cost) {
                max_cost = cost;
                idx = i;
            }
        }
        cout << "Case #" << o + 1 << ": " << idx + 1;
        cout << endl;
    }
    return 0;
}
