#include <iostream>
#include <vector>
#include <set>

using namespace std;

std::vector<int> a[100001];
std::vector<int> rev[100001];
enum Label
{
    Win = 0, Lose, None
};
std::vector<Label> res;

int main()
{
    int n, m;
    cin >> n >> m;
    res.resize(n + 1, None);
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

    set<int> to_check;
    for (size_t i = 1; i <= n; ++i)
        if (a[i].empty())
        {
//            cout << "Mark " << i << " lose" << endl;
            res[i] = Lose;
            for (size_t j = 0; j < rev[i].size(); ++j)
                to_check.insert(rev[i][j]);
        }
    while (!to_check.empty())
    {
//        cout << "Next check" << endl;
        set<int> next_check;
        for (int v : to_check)
        {
//            cout << "Checking " << v << endl;
            if (res[v] != None)
                continue;
            int cnt[3] = {0};
            for (size_t i = 0; i < a[v].size(); ++i)
                cnt[res[a[v][i]]] += 1;
            if (cnt[Lose] > 0)
            {
                res[v] = Win;
//                cout << "Mark " << v << " win" << endl;
            }
            else if (cnt[Win] == a[v].size())
            {
                res[v] = Lose;
//                cout << "Mark " << v << " lose" << endl;
            }

            if (res[v] != None)
            {
                for (size_t j = 0; j < rev[v].size(); ++j)
                    next_check.insert(rev[v][j]);
            }
        }
        swap(next_check, to_check);
    }
    int v;
    cin >> v;
    switch (res[v])
    {
    case None:
        cout << "Draw";
        return 0;
    case Lose:
        cout << "Lose";
        return 0;
    case Win:
    {
        cout << "Win\n";
        while (!a[v].empty())
        {
            cout << v << " ";
            if (res[v] == Win)
            {
                 for (size_t j = 0; j < a[v].size(); ++j)
                    if (res[a[v][j]] == Lose)
                        v = a[v][j];
            }
            else
            {
                v = a[v].front();
            }
        }
        cout << v;
        return 0;
    }
    }
    return 0;
}
