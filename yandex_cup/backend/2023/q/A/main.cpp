#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    uint64_t res = 0;
    vector<uint64_t> decr(m, 0), a;
    for (int i = 0; i < m; ++i)
    {
        uint64_t val;
        cin >> val;
        res += val * val;
        if (val > 0)
        {
            a.push_back(val);
        }
    }
    for (int i = 0; i < a.size(); ++i)
    {
        if (i + a[i] < a.size())
        {
            decr[i + a[i]] += 1;
        }
    }
    int cnt = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        // cout << cnt << " " << a[i] << endl;
        res += cnt * a[i];
        ++cnt;
        cnt -= decr[i];
    }
    cout << res << endl;
    return 0;
}
