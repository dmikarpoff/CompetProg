#include <iostream>

using namespace std;

int main()
{
    string j, s;
    cin >> j >> s;
    int cnt = 0;
    for (auto c : s) {
        if (j.find(c) != string::npos)
            ++cnt;
    }
    cout << cnt << endl;
    return 0;
}
