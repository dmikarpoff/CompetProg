#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

using namespace std;

enum Action
{
    INC,
    DEC,
    NOP
};

int main()
{
    int n;
    cin >> n;
    int min_response = 1000;
    int max_response = 1;
    int b = 1;
    int ok = 0;
    vector<int> total(1001, 0);
    vector<int> failed(1001, 0);
    constexpr int kBatchSize = 100;
    cerr << "========================================================================" << endl;
    set<int> estimated;
    // Find first triggered
    for (int i = 0;; ++i)
    {
        cout << b << endl;
        ++total[b];
        int t;
        cin >> t;
        if (t == -1)
        {
            ++failed[b];
        }
        else
        {
            ++ok;
            min_response = t;
            max_response = t;
            break;
        }
        if (i % 2 == 1)
        {
            b = min(b * 2, (1001 + b) / 2);
        }
    }

    vector<int> tried(1001, 0);
    bool stop = false;
    // Looking for best b
    for (int i = 0; ; ++i)
    {
        cout << b << endl;
        ++total[b];
        int t;
        cin >> t;
        if (t == -1)
        {
            ++failed[b];
        }
        else
        {
            tried[b]++;
            ++ok;
            min_response = min(min_response, t);
            max_response = max(max_response, t);
        }
        if (ok == n)
        {
            return 0;
        }

        if (i % kBatchSize + 1 != kBatchSize || stop)
        {
            continue;
        }

        double p = 1.0;
        for (int j = max_response + 1; j <= 1000; ++j)
        {
            for (int h = 0; h < tried[j]; ++h)
            {
                p *= static_cast<double>(max_response - min_response + 1) / (j - min_response + 1);
            }
        }
        cerr << "Probability = " << p << endl;
        if (p < 1e-5)
        {
            cerr << "Fixing max_response = " << max_response << endl;
            stop = true;
            b = max_response;
        }
        else
        {
            b = min(2 * b, (b + 1001) / 2);
            cerr << "Increse to " << b << endl;
        }

        // Analyze statistics

        /*
        for (int s = max_response; s <= 1000; ++s)
        {
            vector<double> estimated_p;
            for (int j = 1; j <= 1000; ++j)
            {
                if (total[j] == 0)
                {
                    continue;
                }
                double p_calc = static_cast<double>(failed[j]) / total[j];
                if (j < s)
                {
                    double extra_fail = static_cast<double>(s - j) / (s - min_response + 1);
                    double prob_ok = static_cast<double>(j - min_response + 1) / (s - min_response + 1);
                    if (extra_fail > p_calc)
                    {
                        estimated_p.push_back(0.0);
                    }
                    else
                    {
                        estimated_p.push_back((p_calc - extra_fail) / prob_ok);
                    }
                }
                else
                {
                    estimated_p.push_back(p_calc);
                }
            }
        }
        */
    }
}
