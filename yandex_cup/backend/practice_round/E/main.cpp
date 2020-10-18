#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, vector<int>> adj;
unordered_map<int, char> component;
int component_num = 0;

void dfs(int v) {
    component[v] = component_num;
    for (auto u : adj[v]) {
        if (component[u] == -1) {
            dfs(u);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        component[a] = -1;
        component[b] = -1;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (auto& v: component) {
        if (v.second == -1) {
            dfs(v.first);
            ++component_num;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, k;
        cin >> x >> k;
        vector<int> res;
        int q_comp = component[x];
        for (int j = 0; j < k; ++j) {
            int y;
            cin >> y;
            auto it = component.find(y);
            if (it != component.end() && it->second == q_comp) {
                res.push_back(y);
            }
        }
        cout << res.size() << " ";
        for (auto x : res) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
