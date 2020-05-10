#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        auto min_letter = count(s.begin(), s.end(), s[0]);
        if (min_letter < k || k == n)
        {
            cout << s[k - 1] << endl;
            continue;
        }
        if (s[k] == s.back())
        {
            string res = "";
            res += s[0];
            for (int i = 0; i < (n - k) / k; ++i)
                res += s[k];
            if ((n - k) % k)
                res += s[k];
            cout << res << endl;
        }
        else
        {
            cout << (s[0] + string(s.begin() + k, s.end())) << endl;
        }
    }
    return 0;
}
