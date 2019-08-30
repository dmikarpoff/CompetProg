#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

struct Point
{
    int x;
    int y;
};

int main()
{
    Point missle;
    cin >> missle.x >> missle.y;
    int n;
    cin >> n;
    Point poly[101];
    for (int i = 0; i < n; ++i)
        cin >> poly[i].x >> poly[i].y;
    bool inside = true;
    double min_d = 1E+9;
    for (int i = 0; i < n; ++i)
    {
        const auto& v1 = poly[i];
        const auto& v2 = poly[(i + 1) % n];
        const auto& pt = poly[(i + max(2, n / 2)) % n];
        auto a = v1.y - v2.y;
        auto b = v2.x - v1.x;
        auto c = -a * v1.x - b * v1.y;
        if (static_cast<int64_t>(a * pt.x + b * pt.y + c) *
            static_cast<int64_t>(a * missle.x + b * missle.y + c) < 0)
        {
            inside = false;
        }

        auto a1 = -b;
        auto b1 = a;
        auto c1 = -a1 * missle.x - b1 * missle.y;
        double t = static_cast<double>(-c1 - a1 * v2.x - b1 * v2.y) /
                   (a1 * v1.x - a1 * v2.x + b1 * v1.y - b1 * v2.y);
        if (t >= 0.0 && t <= 1.0)
        {
            double x = v1.x * t + (1 - t) * v2.x;
            double y = v2.y * t + (1 - t) * v2.y;
            double d = abs(a * missle.x + b * missle.y + c) / sqrt(a * a + b * b);
            min_d = min(min_d, d);
//            cout << "d = " << d << endl;
        }
        else
        {
            double lt = hypot(missle.x - v1.x, missle.y - v1.y);
            double rt = hypot(missle.x - v2.x, missle.y - v2.y);
            min_d = min(min(min_d, lt), rt);
            /*
            cout << "lt = " << lt << endl;
            cout << "rt = " << rt << endl;
            cout << "shifted d = " << min(lt, rt) << endl;
            */
        }
    }
    if (inside)
    {
        cout << "0.000" << endl;
        return 0;
    }
    printf("%.3f", 2.0 * min_d);
    cout << endl;
    return 0;
}
