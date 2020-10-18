#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i + 1];
    }
    int m_val = 1000 * 1000;
    vector<int> b(n, -1);
    int i = 0;
    int free_pos = -1;
    while (true) {
        int cur_val = a[i];
        int j = i;
        while (a[j] == a[i] && j < n + 1)
        {
            ++j;
        }
        if (j == n + 1)
        {
            break;
        }
        if (free_pos == -1 && i + 1 != j)
        {
            free_pos = i;
        }
        b[j - 1] = a[i];
        for (int h = a[i] + 1; h < a[j]; ++h)
        {
            if (free_pos == -1)
            {
                cout << -1 << endl;
                return 0;
            }
            b[free_pos] = h;
            int old_pos = free_pos;
            free_pos = -1;
            for (int k = old_pos + 1; k < j - 1; ++k)
            {
                if (b[k] == -1)
                {
                    free_pos = k;
                    break;
                }
            }
        }
        i = j;
    }
    for (auto x : b)
        cout << (x == -1 ? --m_val : x) << " ";
    cout << endl;
    return 0;
}
