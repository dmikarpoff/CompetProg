#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

int n;
int mapping[2001];
int index[2001];
int link[2001];
int mark[2001];
int st[2001];
int stack_top = 0;
int component_num = 0;
int cur_index = 0;

void dfs(int v, const vector<vector<int>>& adj)
{
//    cout << "Start search from " << v << endl;
    mark[v] = 1;
    index[v] = cur_index++;
    link[v] = index[v];
    st[stack_top++] = v;
//    cout << "Index of node = " << index[v] << endl;
    for (auto u : adj[v])
    {
        if (mark[u] == 0)
        {
            dfs(u, adj);
            link[v] = min(link[v], link[u]);
        }
        else
        {
            if (mark[u] == 1)
            {
                link[v] = min(link[v], index[u]);
            }
        }
    }
//    cout << "Leaving vertex " << v << endl;
//    cout << "======= Estimated link = " << link[v] << endl;
    if (link[v] == index[v])
    {
//        cout << "Collecting component from vertex " << v << endl;
        mapping[v] = component_num;
        mark[v] = 2;
        while (stack_top != 0 && st[stack_top - 1] != v )
        {
            auto u = st[--stack_top];
            mapping[u] = component_num;
            mark[u] = 2;
        }
        --stack_top;
        ++component_num;
    }
}

char buffer[10000];

int main()
{
    scanf("%d", &n);
    gets(buffer);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i)
    {
        gets(buffer);
        stringstream ss(buffer);
        int val = 0;
        //sscanf(buffer, "%d", &val);
        ss >> val;
        while (val != 0)
        {
            if (val != i + 1)
            {
                adj[i].push_back(val - 1);
            }
            // scanf("%d", &val);
            ss >> val;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (mark[i] != 0)
            continue;
        dfs(i, adj);
    }

    /*
    for (int i = 0; i < n; ++i)
        cout << mapping[i] << " ";
    cout << endl;
    */

    vector<int> pw(component_num, 0);
    for (size_t i = 0; i < adj.size(); ++i)
    {
        for (auto v : adj[i])
            if (mapping[i] != mapping[v])
            {
                ++pw[mapping[v]];
            }
    }

    /*
    for (auto x : pw)
        cout << x << " ";
    cout << endl;
    */

    auto i = find(pw.begin(), pw.end(), 0);
    if (i == pw.end() || find(i + 1, pw.end(), 0) != pw.end())
    {
        printf("0\n");
        return 0;
    }
    auto r = i - pw.begin();
    for (int i = 0; i < n; ++i)
        if (mapping[i] == r)
            printf("%d ", i + 1);
    printf("0\n");
    return 0;
}
