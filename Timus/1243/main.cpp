#include <iostream>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int res = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
      res = (res * 10 + s[i] - '0') % 7;
    }
    cout << res;
    return 0;
}
