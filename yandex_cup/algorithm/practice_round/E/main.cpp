#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(int v, const vector<vector<int>>& adj, vector<int>& dst, vector<int>& p)
{
    int d = dst[v];
    auto ret = 0;
    for (auto u : adj[v]) {
        if (dst[u] == -1) {
            dst[u] = d + 1;
            p[u] = v;
            ret = max(ret, d + 1);
            ret = max(ret, dfs(u, adj, dst, p));
        }
    }
    return ret;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    vector<int> dst(n, -1);
    vector<int> p(n, -1);
    dst[0] = 0;
    dfs(0, adj, dst, p);
    int d1 = 0;
    for (int i = 0; i < n; ++i) {
        if (dst[i] > dst[d1]) {
            d1 = i;
        }
    }
    fill(dst.begin(), dst.end(), -1);
    fill(p.begin(), p.end(), -1);
    dst[d1] = 0;
    dfs(d1, adj, dst, p);
    int d2 = 0;
    for (int i = 0; i < n; ++i)
        if (dst[i] > dst[d2]) {
            d2 = i;
        }
    std::vector<int> base;
    for (int v = d2; v != -1; v = p[v]) {
        base.push_back(v);
    }
    int u_idx = base.size() / 2 + (base.size() % 2 == 0 ? -1 : 0);
    int v_idx = base.size() / 2;
    int dist_u = u_idx;
    int dist_v = u_idx;
    fill(dst.begin(), dst.end(), -1);
    for (auto v: base) {
//        cout << v << " ";
        dst[v] = 0;
    }
//    cout << endl;
    vector<int> depth(base.size(), 0);
    for (size_t i = 0; i < base.size(); ++i)
    {
        depth[i] = dfs(base[i], adj, dst, p);
//        cout << depth[i] << ' ';
    }
//    cout << endl;
    for (;;) {
        if (dist_u == 0 && dist_v == 0) {
            break;
        }
        if (dist_v > dist_u) {
            depth[v_idx + 1] = max(depth[v_idx + 1], depth[v_idx] + 1);
            if (depth[v_idx + 1] < dist_v) {
                --dist_v;
                ++v_idx;
            } else {
                break;
            }
        } else {
            depth[u_idx - 1] = max(depth[u_idx - 1], depth[u_idx] + 1);
            if (depth[u_idx - 1] < dist_u) {
                --dist_u;
                --u_idx;
            } else {
                break;
            }
        }
    }
    if (u_idx == v_idx) {
        v_idx = (u_idx + 1) % base.size();
    }
    cout << base[u_idx] + 1 << " " << base[v_idx] + 1;
    return 0;
}

/*

12
1 2
2 3
2 4
4 5
5 12
5 6
6 9
6 7
7 8
9 10
9 11

14
1 3
2 3
3 4
4 5
4 14
4 6
6 7
6 8
13 10
13 11
10 9
11 12
13 14

*/
