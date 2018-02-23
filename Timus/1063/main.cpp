#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> adj[7];
int comp[7];

void dfs(int x, int mark, int* status, const std::vector<int>* adj)
{
    status[x] = mark;
    for (size_t i = 0; i < adj[x].size(); ++i)
        if (status[adj[x][i]] == -1)
        {
            status[adj[x][i]] = mark;
            dfs(adj[x][i], mark, status, adj);
        }
}

int main()
{
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= 6; ++i)
        comp[i] = -1;
    int comp_num = 0;
    for (int i = 1; i <= 6; ++i)
        if (comp[i] == -1 && !adj[i].empty())
            dfs(i, comp_num++, comp, adj);
    std::vector<int> perm;
    for (int i  = 0; i < comp_num; ++i)
        perm.push_back(i);
    vector<vector<int> > groups(comp_num);
    for (int i = 1; i <= 6; ++i)
        if (comp[i] != -1)
            groups[comp[i]].push_back(i);

    int min_fee = 1000000;
    vector<pair<int, int>> res;
    do
    {
        vector<int> bridges(2 * comp_num, 0);
//        cout << "Next permut" << endl;
        do
        {
//            cout << "-------" << endl;
//            for (int i = 0; i < bridges.size(); ++i)
//                cout << bridges[i] << " ";
//            cout << endl;
            int fee = 0;
            vector<pair<int, int>> t_res;
            vector<int> upd_adj[7] = adj;
            for (size_t i = 0; i < groups.size() - 1; ++i)
            {
                int u = groups[perm[i]][bridges[2 * perm[i] + 1]];
                int v = groups[perm[i + 1]][bridges[2 * perm[i + 1]]];
//                cout << "Adding " << u << " " << v << endl;
                t_res.emplace_back(u, v);
                fee += u + v;
                upd_adj[u].push_back(v);
                upd_adj[v].push_back(u);
            }

            vector<int> odd;
            for (int i = 1; i <= 6; ++i)
                if (upd_adj[i].size() % 2)
                    odd.push_back(i);
            while (odd.size() > 2)
            {
                fee += odd[0] + odd[1];
                t_res.emplace_back(odd[0], odd[1]);
                odd.erase(odd.begin(), odd.begin() + 2);
            }

            if (fee < min_fee)
            {
                min_fee = fee;
                res = t_res;
            }
            bridges.front()++;
            for (size_t i = 0; i < bridges.size() - 1; ++i)
            {
                if (bridges[i] == groups[i / 2].size())
                {
                    bridges[i + 1]++;
                    bridges[i] = 0;
                }
                else
                {
                    break;
                }
            }
        }
        while (bridges.back() != groups.back().size());
    }
    while (next_permutation(perm.begin(), perm.end()));
    cout << min_fee << endl;
    cout << res.size() << endl;
    for (const auto& p : res)
        cout << p.first << " " << p.second << endl;
    return 0;
}
