#include <iostream>
#include <string>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 1; o <= T; ++o)
    {
        string s;
        cin >> s;
        string res;
        int state = 0;
        for (size_t i = 0; i < s.size(); ++i)
        {
            int delta = (s[i] - '0') - state;
            if (delta != 0)
            {
                res += delta > 0 ? string(delta, '(') : string(-delta, ')');
            }
            res += s[i];
            state = (s[i] - '0');
        }
        if (state != 0) {
            res += string(state, ')');
        }
        cout << "Case #" << o << ": ";
        cout << res << endl;
    }
    return 0;
}
