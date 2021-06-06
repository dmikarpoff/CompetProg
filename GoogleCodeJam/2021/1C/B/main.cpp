#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

bool my_le(const std::string& lhs, const std::string& rhs)
{
    if (lhs.size() < rhs.size())
    {
        return true;
    }
    if (lhs.size() > rhs.size())
    {
        return false;
    }
    return lhs <= rhs;
}

int main()
{
    int t;
    cin >> t;
    for (int o = 1; o <= t; ++o)
    {
        string s;
        cin >> s;
        size_t sz = s.size();
        string res;
        for (int p = 1; p <= 10 && p <= s.size(); ++p)
        {
            // cout << "p = " << p << endl;
            string start = s.substr(0, p);
            for (int a = 0; a <= 1; ++a)
            {
                auto i = stoll(start) + a;
                // cout << "Starting from " << i << endl;
                string g;
                int cnt = 0;
                while (my_le(g, s) || cnt <= 1)
                {
                    g += to_string(i);
                    ++i;
                    ++cnt;
                }
                if (res.empty() || my_le(g, res))
                {
                    res = std::move(g);
                }
            }
            {
                int i = 1;
                for (int j = 0; j < p - 1; ++j)
                {
                    i *= 10;
                }
                string g;
                int cnt = 0;
                while (my_le(g, s) || cnt <= 1)
                {
                    g += to_string(i);
                    ++i;
                    ++cnt;
                }
                if (res.empty() || my_le(g, res))
                {
                    res = std::move(g);
                }
            }
            {
                int x = 1;
                for (int j = 0; j < p; ++j)
                {
                    x *= 10;
                }
                --x;
                int d = s.size() / p + 1;
                for (int h = 1; h <= d; ++h)
                {
                    int i = x - h + 1;
                    if (i <= 0)
                    {
                        continue;
                    }
                    string g;
                    int cnt = 0;
                    while (my_le(g, s) || cnt <= 1)
                    {
                        g += to_string(i);
                        ++i;
                        ++cnt;
                    }
                    if (res.empty() || my_le(g, res))
                    {
                        res = std::move(g);
                    }
                }
            }
        }
        cout << "Case #" << o << ": ";
        cout << res;
        cout << endl;
    }
    return 0;
}
