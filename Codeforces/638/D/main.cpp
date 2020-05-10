#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int64_t n;
        cin >> n;
        vector<int64_t> s;
        int64_t sum = 1;
        s.push_back(1);
        while (n - sum > 2 * s.back())
        {
            auto r = min((n - sum) / 2, 2 * s.back());
            s.push_back(r);
            sum += r;
//            cout << "---" << r << " " << sum << endl;
        }
        s.push_back(n - sum);
        cout << s.size() - 1 << endl;
        for (size_t i = 0; i + 1 < s.size(); ++i)
            cout << s[i + 1] - s[i] << " ";
        cout << endl;
    }
    return 0;
}
