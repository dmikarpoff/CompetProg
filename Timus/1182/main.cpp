#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int adj[100][100];

template <class T>
int diff(const T& pair_vv)
{
    return static_cast<int>(pair_vv.first.size()) - pair_vv.second.size();
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int v = 0;
        cin >> v;
        while (v != 0)
        {
            adj[i][v - 1] = 1;
            cin >> v;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adj[j][i] == 0) {
                adj[i][j] = 0;
            }
        }
    }
    vector<vector<int>> a(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adj[i][j] == 0 && i != j) {
                a[i].push_back(j);
            }
        }
    }
    vector<char> used(n, 0);
    vector<pair<vector<int>, vector<int>>> colored;
    bool impossible = false;
    for (int i = 0; i < n; ++i) {
        if (used[i] != 0)
        {
            continue;
        }
        colored.emplace_back();
        queue<int> q;
        q.push(i);
        used[i] = 1;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            int color = 3 - used[v];
            if (used[v] == 1)
            {
                colored.back().first.push_back(v);
            }
            else
            {
                colored.back().second.push_back(v);
            }

            for (auto u : a[v])
            {
                if (used[u] == 0)
                {
                    used[u] = color;
                    q.push(u);
                }
                else
                {
                    if (used[u] != color)
                    {
                        //cout << "Impossible to color " << u << ", " << v << endl;
                        impossible = true;
                    }
                }
            }
        }
    }
    if (impossible)
    {
        cout << "No solution" << endl;
        return 0;
    }
    sort(colored.begin(), colored.end(), [](const auto& lhs, const auto& rhs)
         {
             return abs(diff(lhs)) > abs(diff(rhs));
         });
    vector<int> team[2];
    for (auto& pair_vv : colored)
    {
        int d = diff(pair_vv);
        if ((team[0].size() > team[1].size() && d > 0) || (team[0].size() < team[1].size() && d < 0))
        {
            swap(pair_vv.first, pair_vv.second);
        }
        team[0].insert(team[0].end(), pair_vv.first.begin(), pair_vv.first.end());
        team[1].insert(team[1].end(), pair_vv.second.begin(), pair_vv.second.end());
    }
    for (const auto & t : team)
    {
        cout << t.size() << " ";
        for (auto x : t)
            cout << x + 1 << " ";
        cout << endl;
    }
    return 0;
}
