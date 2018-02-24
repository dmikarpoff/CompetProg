#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, d;
    cin >> n >> d;
    vector<int> x(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i];
    sort(x.begin(), x.end());
    int best = n + 1;
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (x[j] - x[i] <= d)
            {
                int res = i + n - j - 1;
                if (res < best)
                    best = res;
            }
    cout << best;
    return 0;
}
