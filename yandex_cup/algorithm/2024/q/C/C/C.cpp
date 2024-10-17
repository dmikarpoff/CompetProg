#include <algorithm>
#include <iostream>

int main()
{
    std::string s;
    std::cin >> s;
    int l = 0, r = 0;
    int pos = 0;
    for (auto c : s)
    {
        if (c == 'L' || c == '?')
        {
            --pos;
            l = std::min(l, pos);
        }
        else
        {
            ++pos;
            r = std::max(r, pos);
        }
    }
    auto dif = r - l;
    l = r = pos = 0;
    for (auto c : s)
    {
        if (c == 'L')
        {
            --pos;
            l = std::min(l, pos);
        }
        else
        {
            ++pos;
            r = std::max(r, pos);
        }
    }
    std::cout << (dif > r - l ? dif : r - l) << std::endl;
}
