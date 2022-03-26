#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<tuple<int, int, int>> todo;
    for (int i = 0; i < n; ++i)
    {
        int t, d;
        cin >> t >> d;
        todo.push_back(make_tuple(t, d, i));
    }
    sort(todo.begin(), todo.end(), [](const auto& lhs, const auto& rhs) {return get<1>(lhs) < get<1>(rhs);});

    /*
    for (const auto & td : todo)
    {
        cout << get<0>(td) << " " << get<1>(td) << " " << get<2>(td) << endl;
    }
    */

    vector<uint64_t> user(k, 0);
    vector<vector<int>> res(k);
    bool failed = false;
    for (const auto& td : todo)
    {
        size_t min_user = 0;
        for (size_t i = 0; i < k; ++i)
        {
            if (user[i] < user[min_user])
            {
                min_user = i;
            }
        }
        user[min_user] += get<0>(td);
        if (user[min_user] > get<1>(td))
        {
            failed = true;
            break;
        }
        res[min_user].push_back(get<2>(td) + 1);
    }
    if (failed)
    {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    for (size_t i = 0; i < k; ++i)
    {
        cout << res[i].size() << " ";
        for (auto x : res[i])
        {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
