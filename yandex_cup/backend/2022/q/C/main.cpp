#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>

using namespace std;

uint64_t char_to_num(char c)
{
    if (c <= '9' && c >= '0')
        return c - '0';
    return c - 'A' + 10;
}

void add(std::vector<uint64_t>& sum, const std::string& v)
{
    for (int i = v.size() - 1, j = 0; i >= 0; --i, ++j)
    {
        if (sum.size() < v.size())
        {
            sum.resize(v.size(), 0);
        }
        sum[j] += char_to_num(v[i]);
    }
}

int main()
{
    std::ifstream in("input.txt");
    ofstream out("output.txt");
    string str;
    bool is_left = true;
    bool is_pos = true;
    char max_digit = '0';
    vector<uint64_t> left_sum(1, 0);
    vector<uint64_t> right_sum(1, 0);
    while (in >> str)
    {
        if (str == "=")
        {
            is_left = false;
            is_pos = true;
            continue;
        }
        if (str == "+")
        {
            is_pos = true;
            continue;
        }
        if (str == "-")
        {
            is_pos = false;
            continue;
        }
        for (auto c: str)
        {
            if (c > max_digit)
            {
                max_digit = c;
            }
        }
        if ((is_left && is_pos) || (!is_left && !is_pos))
            add(left_sum, str);
        else
            add(right_sum, str);
    }


    uint64_t min_modulo = char_to_num(max_digit) + 1;
    uint64_t max_modulo = 0;
    for (auto x : left_sum)
        max_modulo = max(max_modulo, x);
    for (auto x : right_sum)
        max_modulo = max(max_modulo, x);
    ++max_modulo;
    max_modulo = max(max_modulo, min_modulo);
    auto len = max(left_sum.size(), right_sum.size());
    left_sum.resize(len, 0);
    right_sum.resize(len, 0);
    size_t first_dif = -1;
    for (int i = 0; i < len; ++i)
    {
        if (left_sum[i] != right_sum[i])
        {
            first_dif = i;
            break;
        }
    }
    if (first_dif == static_cast<size_t>(-1))
    {
        out << min_modulo << endl;
        return 0;
    }
    for (size_t m = min_modulo; m <= max_modulo; ++m)
    {
        if (m > max(left_sum[first_dif], right_sum[first_dif]))
        {
            break;
        }
        if (left_sum[first_dif] % m != right_sum[first_dif] % m)
        {
            continue;
        }
        auto a = left_sum;
        auto b = right_sum;
        bool fail = false;
        for (int i = 0; i + 1 < len; ++i)
        {
            if (a[i] % m != b[i] % m)
            {
                fail = true;
                break;
            }
            a[i + 1] += a[i] / m;
            b[i + 1] += b[i] / m;
        }
        if (!fail && a.back() == b.back())
        {
            out << m << endl;
            return 0;
        }
    }
    out << "-1" << endl;
    return 0;
}
