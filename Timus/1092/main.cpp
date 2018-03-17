#include <iostream>
#include <vector>

using namespace std;

int countPluses(const std::vector<string>& fld)
{
    int res = 0;
    for (const auto& str : fld)
        for (char c : str)
            if (c == '+')
                ++res;
    return res;
}

int main()
{
    int n;
    cin >> n;
    n = 2 * n + 1;
    std::vector<string> fld(n);
    for (int i = 0; i < n; ++i)
        cin >> fld[i];
    cout << "There is solution:" << endl;
    while (countPluses(fld) >= n)
    {
    }
    return 0;
}
