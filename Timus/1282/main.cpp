#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int parent;
    int mark;
    vector<int> children;
    bool leaf = false;
};

vector<Node> nodes;
int dfs(int v, int depth)
{
    int best = -1;
    int worst = 1;
    for (auto u : nodes[v].children)
    {
        auto val = nodes[u].leaf ? nodes[u].mark : dfs(u, depth + 1);
        best = max(best, val);
        worst = min(worst, val);
    }
    return depth % 2 ? worst : best;
}

int main()
{
    int n;
    cin >> n;
    nodes.resize(n);
    nodes[0].parent = -1;
    nodes[0].mark = -1;
    for (int i = 1; i < n; ++i)
    {
        string s;
        int p;
        cin >> s >> p;
        nodes[i].parent = p - 1;
        nodes[p - 1].children.push_back(i);
        if (s == "L")
        {
            int mark;
            cin >> mark;
            nodes[i].mark = mark;
            nodes[i].leaf = true;
        }
    }
    auto res = dfs(0,0);
    if (res > 0)
        cout << '+';
    cout << dfs(0, 0) << endl;
    return 0;
}
