#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Interval
{
    int from;
    int till;
    int id;
};

int main()
{
    int T;
    cin >> T;
    for (int o = 1; o <= T; ++o)
    {
        int n;
        cin >> n;
        vector<Interval> tasks(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> tasks[i].from >> tasks[i].till;
            tasks[i].id = i;
        }
        sort(tasks.begin(), tasks.end(),
             [](const auto& lhs, const auto& rhs)
             {
                 return (lhs.from < rhs.from) || (lhs.from == rhs.from && lhs.till < rhs.till);
             }
        );
        int j = -1;
        int c = -1;
        string res(n, 'x');
        bool impossible = false;
        for (const auto i : tasks)
        {
            if (impossible)
            {
                break;
            }
            if (j == -1 || j <= i.from)
            {
                j = i.till;
                res[i.id] = 'J';
                continue;
            }
            if (c == -1 || c <= i.from)
            {
                c = i.till;
                res[i.id] = 'C';
                continue;
            }
            impossible = true;
            break;
        }
        cout << "Case #" << o << ": ";
        cout << (impossible ? "IMPOSSIBLE" : res.c_str()) << endl;
    }
    return 0;
}
