#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

// vector<int> st;

map<int, int> dp[1000 * 1000 + 1];

void lookup(int m, int r, int& res, int depth)
{
    // cout << "Look up from " << m << " " << r << " " << depth << endl;
    if (r == 0)
    {
        if (depth > res)
        {
            res = depth;
        }
        /*
        for (auto x : st)
        {
            cout << x << " ";
        }
        cout << endl;
        */
        return;
    }

    if (r < 3)
    {
        return;
    }
    for (int j = 2; j * j <= m; ++j)
    {
        if (m % j == 0)
        {
            // st.push_back(j);
            if (j >= 3)
            {
                // cout << "Trying " << j << endl;
                if (j <= 100000)
                {
                    auto it = dp[j].find(r);
                    if (it != dp[j].end() && res < depth + it->second)
                    {
                        res = depth + it->second;
                    }
                }
                else
                {
                    lookup(j, r - j, res, depth + 1);
                }
            }
            //st.pop_back();
            if (j != m / j && m / j >= 3)
            {
                // cout << "Trying " << m / j << endl;
                if (m / j <= 100000)
                {
                    auto it = dp[m / j].find(r);
                    if (it != dp[m / j].end() && res < depth + it->second)
                    {
                        res = depth + it->second;
                    }
                }
                else
                {
                    lookup(m / j, r - m / j, res, depth + 1);
                }
                // st.push_back(m / j);
                // st.pop_back();
            }
        }
    }
}

struct Data
{
    uint64_t depth;
    uint64_t sum;
};

bool operator<(const Data& lhs, const Data& rhs)
{
    return lhs.sum < rhs.sum;
}


int main()
{
    int t;
    for (int i = 3; i <= 1000; ++i)
    {
        auto& s = dp[i];
        s[i] = 1;
        for (int j = 2; j * j <= i; ++j)
        {
            if (i % j == 0)
            {
                if (j > 2)
                {
                    for (const auto& d : dp[j])
                    {
                        Data x{d.second + 1, d.first + i};
                        auto it = dp[i].find(x.sum);
                        if (it == dp[i].end())
                        {
                            dp[i][x.sum] = x.depth;
                        }
                        else if (it->second < x.depth)
                        {
                            it->second = x.depth;
                        }
                    }
                }

                int h = i / j;
                if (h > 2)
                {
                    for (const auto& d : dp[h])
                    {
                        Data x{d.second + 1, d.first + i};
                        auto it = dp[i].find(x.sum);
                        if (it == dp[i].end())
                        {
                            dp[i][x.sum] = x.depth;
                        }
                        else if (it->second < x.depth)
                        {
                            it->second = x.depth;
                        }
                    }
                }
            }
        }
    }
    cin >> t;
    for (int o = 1; o <= t; ++o)
    {
        int n;
        cin >> n;
        int res = 0;
        for (int i = 24; i <= 24; ++i)
        {
            // st.push_back(i);
            lookup(i, n - i, res, 1);
            // st.pop_back();
        }
        cout << "Case #" << o << ": " << res;
        cout << endl;
    }
    return 0;
}
