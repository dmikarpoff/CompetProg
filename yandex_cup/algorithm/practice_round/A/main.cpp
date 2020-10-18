#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int q[10];
    for (int i = 0; i < 10; ++i)
        cin >> q[i];
    sort(begin(q), end(q));
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < 6; ++j) {
            int x;
            cin >> x;
            if (binary_search(begin(q), end(q), x)) {
                ++cnt;
            }
        }
        cout << (cnt >= 3 ? "Lucky" : "Unlucky") << endl;
    }
    return 0;
}
