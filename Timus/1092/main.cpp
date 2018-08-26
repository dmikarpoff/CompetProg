#include <iostream>
#include <vector>
#include <algorithm>

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

bool dfs(size_t idx, const vector<vector<int>>& adj,
         vector<int>& perm, vector<int>& rev_perm,
         vector<bool>& used)
{
    if (used[idx])
        return false;
    used[idx] = true;
    for (auto to : adj[idx])
        if (rev_perm[to] == -1 || dfs(rev_perm[to], adj,
                                      perm, rev_perm, used))
        {
            perm[idx] = to;
            rev_perm[to] = idx;
            return true;
        }
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
        std::vector<int> plus_in_col(n, 0);
        std::vector<int> plus_in_row(n, 0);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                if (fld[i][j] == '+')
                {
                    plus_in_row[i]++;
                    plus_in_col[j]++;
                }
        auto p1 = find_if(plus_in_row.begin(), plus_in_row.end(),
                          [](int x) {return x > 2;});
        auto p2 = find(plus_in_row.begin(), plus_in_row.end(), 0);
        if (p1 != plus_in_row.end() && p2 != plus_in_row.end())
        {
//            cout << "Moving overflowed row to empty row" << endl;
            size_t i_triplet = p1 - plus_in_row.begin();
            size_t i_empty = p2 - plus_in_row.begin();
//            cout << "With triplet " << i_triplet << endl;
//            cout << "Empty one " << i_empty << endl;
            size_t j1 = -1, j2 = -1;
            for (size_t i = 0; i < n; ++i)
                if (fld[i_triplet][i] == '+')
                {
                    if (j1 == static_cast<size_t>(-1))
                    {
                        j1 = i;
                    }
                    else
                    {
                        j2 = i;
                        break;
                    }
                }
            vector<int> perm1(n), perm2(n);
            perm1[i_triplet] = j1;
            perm1[i_empty] = j2;
            perm2[i_triplet] = j2;
            perm2[i_empty] = j1;
            for (size_t i = 0, j = 0; i < n; ++i)
            {
                if (i == i_triplet || i == i_empty)
                    continue;
                while (j == j1 || j == j2)
                    ++j;
                perm1[i] = j;
                perm2[i] = j;
                ++j;
            }
            fld[i_triplet][j1] = fld[i_triplet][j2] = '-';
            fld[i_empty][j1] = fld[i_empty][j2] = '+';
            for (size_t x : perm1)
                cout << x + 1 << " ";
            cout << endl;
            for (size_t x : perm2)
                cout << x + 1 << " ";
            cout << endl;
            continue;
        }

        p1 = find_if(plus_in_col.begin(), plus_in_col.end(),
                     [](int x) {return x > 2;});
        p2 = find(plus_in_col.begin(), plus_in_col.end(), 0);
        if (p1 != plus_in_col.end() && p2 != plus_in_col.end())
        {
//            cout << "Moving overflowed row to empty row" << endl;
            size_t i_triplet = p1 - plus_in_col.begin();
            size_t i_empty = p2 - plus_in_col.begin();
//            cout << "With triplet " << i_triplet << endl;
//            cout << "Empty one " << i_empty << endl;
            size_t j1 = -1, j2 = -1;
            for (size_t i = 0; i < n; ++i)
                if (fld[i][i_triplet] == '+')
                {
                    if (j1 == static_cast<size_t>(-1))
                    {
                        j1 = i;
                    }
                    else
                    {
                        j2 = i;
                        break;
                    }
                }
            vector<int> perm1(n), perm2(n);
            perm1[i_triplet] = j1;
            perm1[i_empty] = j2;
            perm2[i_triplet] = j2;
            perm2[i_empty] = j1;
            for (size_t i = 0, j = 0; i < n; ++i)
            {
                if (i == i_triplet || i == i_empty)
                    continue;
                while (j == j1 || j == j2)
                    ++j;
                perm1[i] = j;
                perm2[i] = j;
                ++j;
            }
            fld[j1][i_triplet] = fld[j2][i_triplet] = '-';
            fld[j1][i_empty] = fld[j2][i_empty] = '+';
            vector<int> temp(n);
            for (size_t i = 0; i < n; ++i)
                temp[perm1[i]] = i + 1;
            for (auto x : temp)
                cout << x << " ";
            cout << endl;
            for (size_t i = 0; i < n; ++i)
                temp[perm2[i]] = i + 1;
            for (auto x : temp)
                cout << x << " ";
            cout << endl;
            continue;
        }

        vector<int> perm(n, -1), rev_perm(n, -1);
        vector<vector<int> > adj(n);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                if (fld[i][j] == '+')
                    adj[i].push_back(j);
        bool found = false;
        do
        {
            found = false;
            for (size_t i = 0; i < n; ++i) {
                std::vector<bool> used(n, false);
                if (perm[i] == -1 && dfs(i, adj, perm, rev_perm,
                                         used))
                    found = true;
            }
        }
        while (found);
        for (size_t i = 0, j = 0; i < n; ++i)
        {
            if (perm[i] == -1)
            {
                while (rev_perm[j] != -1)
                    ++j;
                perm[i] = j;
                ++j;
            }
            fld[i][perm[i]] = (fld[i][perm[i]] == '-' ? '+' : '-');
            cout << perm[i] + 1 << " ";
        }
        cout << endl;
//        for (const auto& s : fld)
//            cout << s << endl;
//        cout << endl;
    }
    return 0;
}
