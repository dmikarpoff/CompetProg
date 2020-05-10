#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

int main()
{
    int64_t n;
    cin >> n;
    int64_t a = n;
    vector<int> digits;
    while (a > 0)
    {
        digits.push_back(a % 3);
        a /= 3;
    }
    int64_t m = 1;
    size_t i = 0;
    int64_t sum = 0;
    while (sum <= n)
    {
        if (i >= digits.size() || digits[i] == 1)
        {
            sum += m;
            m *= 3;
            ++i;
            continue;
        }
        if (digits[i] == 0)
        {
            ++i;
            m *= 3;
            continue;
        }
        while (i < digits.size() && digits[i] != 0)
        {
            ++i;
            m *= 3;
        }
        sum += m;
    }
    cout << sum << " " << sum - n << endl;
    return 0;
}
