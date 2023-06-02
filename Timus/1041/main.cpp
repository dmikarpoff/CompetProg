#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

struct CostIdx
{
    size_t idx;
    int cost;
};

vector<vector<int64_t>> v;
vector<CostIdx> c;

void printMat(const std::vector<std::vector<int64_t>>& mat)
{
    for (size_t i = 0; i < mat.size(); ++i)
    {
        for (size_t j = 0; j < mat[i].size(); ++j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

vector<vector<int64_t>> upper_triangle;
vector<size_t> key_elem;

bool check(size_t idx, int64_t modulo)
{
    auto next_vec = v[idx];
    if (!upper_triangle.empty() && upper_triangle.size() > upper_triangle.front().size())
        return false;
    for (size_t i = 0; i < upper_triangle.size(); ++i)
    {
        if (next_vec[key_elem[i]] == 0)
        {
            continue;
        }
        int64_t root = upper_triangle[i][key_elem[i]];
        int64_t next_root = next_vec[key_elem[i]];
        for (size_t h = 0; h < next_vec.size(); ++h)
        {
            next_vec[h] = (modulo - next_root * upper_triangle[i][h] % modulo +
                           root * next_vec[h] % modulo) % modulo;
        }
    }
    for (size_t i = 0; i < next_vec.size(); ++i)
    {
        if (next_vec[i] != 0)
        {
            upper_triangle.emplace_back(move(next_vec));
            key_elem.push_back(i);
            return true;
        }
    }
    return false;
}

int main()
{
    size_t n, m;
    cin >> m >> n;
    v.resize(m);
    for (size_t i = 0; i < m; ++i)
    {
        v[i] = vector<int64_t>(n, 0);
        for (size_t j = 0; j < n; ++j)
        {
            cin >> v[i][j];
        }
    }
    c.resize(m);
    for (size_t i = 0; i < m; ++i)
    {
        cin >> c[i].cost;
        c[i].idx = i;
    }
    std::stable_sort(c.begin(), c.end(),
              [](const CostIdx& lhs, const CostIdx& rhs)
              {
                 return lhs.cost < rhs.cost;
              });

    std::vector<size_t> idx_list;
    std::vector<int64_t> mods = {27644437};
    size_t cost = 0;
    for (size_t i = 0; i < c.size(); ++i)
    {
        idx_list.push_back(c[i].idx);
        cost += c[i].cost;
        bool indep = true;
        for (size_t mod : mods)
        {
            indep = (indep && check(c[i].idx, mod));
            if (!indep)
            {
                break;
            }
        }
        if (!indep)
        {
            idx_list.pop_back();
            cost -= c[i].cost;
        }
        if (idx_list.size() == n)
            break;
    }
    if (idx_list.size() < n)
    {
        cout << "0\n";
        return 0;
    }
    cout << cost << endl;
    std::sort(idx_list.begin(), idx_list.end());
    for (size_t i = 0; i < idx_list.size(); ++i)
        cout << idx_list[i] + 1 << "\n";
    return 0;
}
