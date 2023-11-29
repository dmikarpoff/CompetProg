#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdint>

using namespace std;

struct Adj
{
    size_t dst;
    double val;
};

unordered_map<string, size_t> colors;
vector<Adj> adj[201];
double upper_lim[201];
bool used[201];
int res = -1;

void dfs(size_t idx, double val)
{
    if (res >= 0)
    {
        return;
    }
    for (auto& a : adj[idx])
    {
        if (val * a.val > upper_lim[idx])
        {
            res = a.dst;
            return;
        }
    }
    for (auto& a : adj[idx])
    {
        if (!used[a.dst])
        {
            used[a.dst] = true;
            dfs(a.dst, val * a.val);
            used[a.dst] = false;
        }
    }
}

double a[201][201];

int main()
{
    size_t node_cnt = 0;
    std::string start;
    cin >> start;
    colors[start] = node_cnt++;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string col;
        double val;
        cin >> col >> val;
        auto it = colors.find(col);
        if (it == colors.end())
        {
            colors[col] = node_cnt++;
        }
        upper_lim[colors[col]] = val;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        string col1, col2;
        double val;
        cin >> col1 >> col2 >> val;
        a[colors[col1]][colors[col2]] = val;
    }
    for (size_t i = 0; i < n; ++i)
    {
        a[i][i] = 1.0;
    }
    std::vector<double> v(n, 0.0);
    vector<double> next_v(n, 0.0);
    vector<double> max_val(n, 0.0);
    v[0] = 1.0;
    max_val[0] = 1.0;
    for (;;)
    {
        for (int i = 0; i < n; ++i)
        {
            next_v[i] = max_val[i];
            for (int j = 0; j < n; ++j)
                next_v[i] = max(next_v[i], a[j][i] * v[j]);
        }
        for (int i = 0; i < n; ++i)
            if (next_v[i] > upper_lim[i])
        {
            res = i;
            break;
        }
        if (res >= 0)
            break;
        bool no_progress = true;
        for (int i = 0; i < n; ++i)
        {
            //cout << next_v[i] << " ";
            if (next_v[i] > max_val[i])
            {
                max_val[i] = next_v[i];
                no_progress = false;
            }
        }
        //cout << endl;
        if (no_progress)
        {
            break;
        }
        swap(next_v, v);
    }

    if (res == -1)
    {
        cout << "None" << endl;
        return 0;
    }
    for (auto& p : colors)
    {
        if (p.second == res)
        {
            cout << p.first << endl;
            return 0;
        }
    }
    return -1;
}
