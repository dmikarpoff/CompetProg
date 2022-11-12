#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> max_path;

void dfs(int v, const vector<vector<int>>& e, vector<int>& path)
{
    if (e[v].empty() && max_path.size() < path.size())
    {
        max_path = path;
    }
    for (auto x : e[v])
    {
        path.push_back(x);
        dfs(x, e, path);
        path.pop_back();
    }
}

int main()
{
    for (int o = 1; o <= 10; ++o)
    {
        string fname = to_string(o) + ".in";
        ifstream in(fname);
        int n, k, a;
        in >> n >> k >> a;
        vector<vector<int>> boxes(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < k; ++j)
            {
                int v;
                in >> v;
                boxes[i].push_back(v);
            }
            sort(boxes[i].begin(), boxes[i].end());
        }
        vector<vector<int>> e(n);
        vector<int> pw(n, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
        {
            bool all = true;
            for (int h = 0; h < k; ++h)
                if (boxes[i][h] >= boxes[j][h])
                {
                    all = false;
                    break;
                }
            if (all)
            {
                e[j].push_back(i);
                pw[i]++;
            }
        }
        cout << "Tree build" << endl;
        for (int i = 0; i < n; ++i)
        {
            if (pw[i] != 0)
            {
                continue;
            }
            vector<int> path;
            path.push_back(i);
            dfs(i, e, path);
        }
        cout << max_path.size() << endl;
        for (auto x: max_path)
        {
            cout << x + 1 << " ";
        }
        cout << endl;
        max_path.clear();
    }
    return 0;
}
