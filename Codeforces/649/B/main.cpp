#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> p[i];
        }
        vector<int> res;
        res.reserve(n);
        bool ascending = (p[1] > p[0]);
        res.push_back(p[0]);
        for (int i = 0; i + 1 < n; ++i)
        {
            bool cur_ascending = (p[i + 1] > p[i]);
            if (ascending != cur_ascending) {
                res.push_back(p[i]);
                ascending = cur_ascending;
            }
        }
        res.push_back(p.back());
        cout << res.size() << endl;
        for (auto x : res) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
