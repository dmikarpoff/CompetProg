#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        vector<int> cnt(n + 1, 0);
        for (auto& x : a)
        {
            cin >> x;
            ++cnt[x];
        }
        auto diff_elem = count_if(cnt.begin(), cnt.end(), [](auto x) {return x > 0;});
        if (diff_elem > k) {
            cout << -1 << endl;
            continue;
        }
        vector<int> r(k, 0);
        vector<int> nice;
        for (int i = 0; i < n;)
        {
            int phase = nice.size() % k;
            if (r[phase] == 0) {
                for (int j = i; j < n; ++j)
                {
                    if (find(r.begin(), r.end(), a[j]) == r.end())
                    {
//                        cout << "Setting " << a[j] << " for phase " << phase << endl;
                        r[phase] = a[j];
                        break;
                    }
                }
                if (r[phase] == 0)
                {
                    r[phase] = a[i];
                }
            }
            nice.push_back(r[phase]);
            if (nice.back() == a[i])
                ++i;
        }
        cout << nice.size() << endl;
        for (auto x : nice)
            cout << x << " ";
        cout << endl;
    }
    return 0;
}
