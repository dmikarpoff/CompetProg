#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <complex>
#include <iomanip>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<complex<int64_t>> data;
    data.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        data.emplace_back(x, y);
    }
    sort(data.begin(), data.end(), [](auto lhs, auto rhs) {return lhs.real() < rhs.real();});
    complex<int64_t> left_sum{0, 0};
    complex<int64_t> right_sum = accumulate(data.begin(), data.end(), complex<int64_t>{0, 0});
    double best_a = 0.0, best_b = 0.0, best_c = 0.0;
    double best_err = 1E+100;
    for (int t = 0; t <= n; ++t) {
        if (t == 0 || t == n || data[t - 1].real() != data[t].real()) {
            double a = (t == 0 ? 0.0 : static_cast<double>(left_sum.imag()) / t);
            double b = (t == n ? 0.0 : static_cast<double>(right_sum.imag()) / (n - t));
            double err = t * a * a - 2 * a * left_sum.imag() + (n - t) * b * b - 2 * b * right_sum.imag();
            if (err < best_err) {
                best_a = a;
                best_b = b;
                if (t == 0) {
                    best_c = data.front().real() - 1.0;
                } else if (t == n) {
                    best_c = data.back().real() + 1.0;
                } else {
                    best_c = 0.5 * (data[t - 1].real() + data[t].real());
                }
                best_err = err;
            }
        }
        if (t != n) {
            left_sum += data[t];
            right_sum -= data[t];
        }
    }
    cout << fixed;
    cout << setprecision(7);
    cout << best_a << " " << best_b << " " << best_c << endl;
    return 0;
}
