#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;
    string res;
    for (size_t i = 0; i + 1 < s.size(); ++i)
        if (s[i] == s[i + 1] && (res.empty() || res[0] > s[i]))
            res = string() + s[i] + s[i];
    if (!res.empty())
    {
        cout << res << endl;
        return 0;
    }
    for (size_t i = 1; i + 1 < s.size(); ++i)
        if (s[i - 1] == s[i + 1]){
            string c = s.substr(i - 1, 3);
            if (res.empty() || c < res)
                res = c;
        }
    cout << (res.empty() ? "-1" : res.c_str()) << endl;
    return 0;
}
