#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    uint64_t res[10] = {0};
    vector<pair<uint64_t, uint64_t>> cnt_nines;
    cnt_nines.push_back(make_pair(0, 1));
    uint64_t pages = 99;
    uint64_t level_num = 9;
    while (pages / 10 < n)
    {
        cnt_nines.push_back(make_pair(
                                10 * cnt_nines.back().first +
                                level_num,
                                10 * cnt_nines.back().second +
                                level_num));
        pages = pages * 10 + 9;
        level_num *= 10;
    }
    for (size_t i = 0; i < cnt_nines.size() - 1; ++i)
    {
        res[0] += cnt_nines[i].first;
        for (int j = 1; j < 10; ++j)
            res[j] += cnt_nines[i].second;
    }
    vector<int> digits;
    while (n > 0)
    {
        digits.push_back(n % 10);
        n /= 10;
    }
    uint64_t prefix[10] = {0};
    for (size_t i = digits.size() - 1; i > 0; --i)
    {
//        cout << "idx = " << i << endl;
        uint64_t cnt = 1;
        for (size_t j = 0; j < i; ++j)
            cnt *= 10;
        uint64_t single_dig = i * cnt / 10;
//        cout << "cnt = " << cnt << endl;
//        cout << "per digit = " << single_dig << endl;
        if (i == digits.size() - 1)
        {
            for (int j = 1; j < digits[i]; ++j)
            {
                res[j] += cnt;
                for (int h = 0; h < 10; ++h)
                    res[h] += single_dig;
            }
        }
        else
        {
            for (int j = 0; j < digits[i]; ++j)
            {
                res[j] += cnt;
                for (int h = 0; h < 10; ++h)
                    res[h] += cnt * prefix[h] + single_dig;
            }
        }
        prefix[digits[i]]++;
    }

    for (size_t i = 0; i <= digits[0]; ++i)
    {
        res[i]++;
        for (int h = 0; h < 10; ++h)
            res[h] += prefix[h];
    }
    if (digits.size() == 1)
        res[0]--;
    for (int i = 0; i < 10; ++i)
        cout << res[i] << endl;
    return 0;
}
