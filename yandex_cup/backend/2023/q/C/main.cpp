#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Eq
{
    double x;
    double y;
    double z;
    double d;
};

int main()
{
    int n;
    cin >> n;
    vector<Eq> eq(n);
    double scale = 0.0;
    double norm = 0.0;
    size_t min_d = 0;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> eq[i].x >> eq[i].y >> eq[i].z >> eq[i].d;
        norm = max(eq[i].d, norm);

        if (eq[i].d < eq[min_d].d)
        {
            min_d = i;
        }

        eq[i].x /= 10000.0;
        eq[i].y /= 10000.0;
        eq[i].z /= 10000.0;
        eq[i].d /= 10000.0;
    }

    for (size_t i = 0; i < eq.size(); ++i)
    {
        if (eq[i].d < 1E-6)
        {
            cout << eq[i].x << " " << eq[i].y << " " << eq[i].z << endl;
            return 0;
        }
    }

    double d = sqrt((eq[0].x - eq[1].x)*(eq[0].x - eq[1].x) + (eq[0].y - eq[1].y) * (eq[0].y - eq[1].y) +
                    (eq[0].z - eq[1].z) * (eq[0].z - eq[1].z));

    double x = eq[min_d].x, y = eq[min_d].y, z = eq[min_d].z;

    for (size_t s = 0; s < 50000; ++s)
    {
        double tgt = 0.0;
        for (int i = 0; i < n; ++i)
        {
            const auto& e = eq[i];
            double dst = (e.x - x) * (e.x - x) + (e.y - y) * (e.y - y) +
                    (e.z - z) * (e.z - z) - e.d * e.d;
            tgt += dst;
        }
        //cout << tgt << endl;
        for (size_t i = 0; i < n; ++i)
        {
            const auto& e = eq[i];
            double dst = (e.x - x) * (e.x - x) + (e.y - y) * (e.y - y) +
                    (e.z - z) * (e.z - z) - e.d * e.d;
            dst *= 2;
            x += dst * (e.x - x);
            y += dst * (e.y - y);
            z += dst * (e.z - z);
        }
    }

    cout << x * 10000.0 << " " << y * 10000.0 << " " << z * 10000.0 << endl;
    //cout << x << " " << y << " " << z << endl;
    return 0;
}
