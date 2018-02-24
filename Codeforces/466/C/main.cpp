#include <iostream>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

int main()
{
    set<char> letter;
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for (char c : s)
        letter.insert(c);

    if (k > n)
    {
        cout << s;
        for (int i = 0; i < k - n; ++i)
            cout << *letter.begin();
        return 0;
    }
    int pos;
    for (int i = 0; i < k; ++i)
        if (s[i] != *letter.rbegin())
            pos = i;
    std::string prefix(s.begin(), s.begin() + pos);
    cout << prefix;
    cout << *upper_bound(letter.begin(), letter.end(), s[pos]);
    for (int i = prefix.size() + 1; i < k; ++i)
        cout << *letter.begin();
    return 0;
}
