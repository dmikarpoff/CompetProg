#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int64_t a = 0, b = 0, c = 0;
    pair<int64_t, int64_t> orig;
    int cnt = 0;
    bool failed = false;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        int64_t x, y;
        if (t == 0) {
            int64_t r;
            cin >> r >> x >> y;
            x *= 2;
            y *= 2;
        } else {
            int64_t x_r[4];
            int64_t y_r[4];
            for (int j = 0; j < 4; ++j)
                cin >> x_r[j] >> y_r[j];
            x = x_r[0] + x_r[2];
            y = y_r[0] + y_r[2];
        }
        if (cnt == 0) {
            orig = {x, y};
            ++cnt;
        } else if (cnt == 1) {
            if (x != orig.first || y != orig.second) {
                a = orig.second - y;
                b = x - orig.first;
                c = -a * x - b * y;
                ++cnt;
            }
        } else if (a * x + b * y + c != 0) {
            failed = true;
        }
    }
    cout << (failed ? "No" : "Yes") << endl;
    return 0;
}
