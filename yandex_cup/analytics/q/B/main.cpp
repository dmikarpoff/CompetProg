#include <iostream>
#include <iomanip>

using namespace std;

bool used[15][4];
int cnt = 0;
int sum = 0;

void foo(int pos) {
    if (pos == 5) {
        int rem_sum = 50 - sum;
        if (rem_sum >= 7 && rem_sum <= 14) {
            for (int i = 0; i < 4; ++i) {
                if (!used[rem_sum][i]) {
                    ++cnt;
                    return;
                }
            }
        }
        return;
    }
    for (int c = 7; c <= 14; ++c) {
        for (int k = 0; k < 4; ++k) {
            if (pos == 0) {
                cout << c << " " << k << " " << cnt << endl;
            }
            if (!used[c][k]) {
                used[c][k] = true;
                sum += c;
                foo(pos + 1);
                sum -= c;
                used[c][k] = false;
            }
        }
    }
}

int main()
{
    uint64_t total = 1;
    for (int i = 0; i < 6; ++i) {
        total *= (32 - i);
    }
    cout << "total = " << total << endl;
    foo(0);
    cout << "count = " << cnt << endl;
    cout << "prob = " << fixed << setprecision(7) << static_cast<double>(cnt) / total << std::endl;
    return 0;
}
