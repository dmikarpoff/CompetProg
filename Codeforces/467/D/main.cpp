#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

std::vector<int> a[100001];
std::vector<int> rev[100001];

struct Prec
{
    int dist = -1;
    int parent = -1;
};

std::vector<Prec> even_dist;
std::vector<Prec> odd_dist;

struct Elem
{
    int vert;
    bool even;
};

vector<int> status;

bool dfs(int x)
{
    if (status[x] == 0)
        return true;
    if (status[x] == 1)
        return false;
    status[x] = 0;
    for (int v : a[x])
        if (dfs(v))
            return true;
    status[x] = 1;
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j)
        {
            int val;
            cin >> val;
            a[i].push_back(val);
            rev[val].push_back(i);
        }
    }

    int origin;
    cin >> origin;

    even_dist.resize(n + 1);
    odd_dist.resize(n + 1);
    queue<Elem> q;
    for (int i = 1; i <= n; ++i)
        if (a[i].empty())
        {
            q.push(Elem{i, true});
            even_dist[i].dist = 0;
        }
    while (!q.empty())
    {
        Elem e = q.front();
        q.pop();
        for (int v : rev[e.vert])
        {
            if (e.even)
            {
                if (odd_dist[v].dist == -1)
                {
                    odd_dist[v].dist = even_dist[e.vert].dist + 1;
                    odd_dist[v].parent = e.vert;
                    q.push(Elem{v, false});
                }
            }
            else
            {
                if (even_dist[v].dist == -1)
                {
                    even_dist[v].dist = odd_dist[e.vert].dist + 1;
                    even_dist[v].parent = e.vert;
                    q.push(Elem{v, true});
                }
            }
        }
    }

    if (even_dist[origin].dist == -1 && odd_dist[origin].dist == -1)
    {
        cout << "Draw";
        return 0;
    }
    if (odd_dist[origin].dist != -1)
    {
        cout << "Win\n";
        while (true)
        {
            cout << origin << " ";
            int p = odd_dist[origin].parent;
            cout << p << " ";
            if (even_dist[p].parent == -1)
                break;
            origin = even_dist[p].parent;
        }
        return 0;
    }
    status.resize(n + 1, -1);
    if (dfs(origin))
    {
        cout << "Draw";
        return 0;
    }
    cout << "Lose";
    return 0;
}
