#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Type {
    UPPER,
    LOWER,
    SPACE
};

int main()
{
    string s;
    getline(cin, s);
    int lower = 0;
    int upper = 2;
    for (auto c : s) {
        if (c == ' ') {
            ++lower;
            ++upper;
            continue;
        }
        int ll = lower;
        int uu = upper;
        if (c > 'Z') {
            lower = min(ll + 1, uu + 3);
            upper = min(uu + 2, ll + 3);
        } else {
            lower = min(ll + 2, uu + 3);
            upper = min(uu + 1, ll + 3);
        }
//        cout << lower << " " << upper << endl;
    }
    cout << min(lower, upper) << endl;
    return 0;
}
