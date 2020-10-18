#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int n, x;
        cin >> n >> x;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<char> used(n + 1);
        used[x] = 1;
        vector<int> subtree;
        for (auto v : adj[x])
        {
            int cnt = 1;
            queue<int> q;
            q.push(v);
            used[v] = 1;
            while (!q.empty()) {
                auto u = q.front();
                q.pop();
                for (auto w : adj[u])
                    if (!used[w])
                    {
                        used[w] = 1;
                        ++cnt;
                        q.push(w);
                    }
            }
            subtree.push_back(cnt);
        }
        if (subtree.size() <= 1 || n % 2 == 0)
        {
            cout << "Ayush" << endl;
        }
        else
        {
            cout << "Ashish" << endl;
        }
    }
    return 0;
}
