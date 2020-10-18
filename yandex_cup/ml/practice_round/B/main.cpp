#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct Pt {
    double x;
    double y;
};

// b ~= 2.715

int main()
{
    ifstream input("data.csv");
    vector<Pt> data;
    while (input) {
        string s;
        getline(input, s);
        replace(s.begin(), s.end(), ',', ' ');
        stringstream ss(s);
        double x, y;
        ss >> x >> y;
        data.push_back(Pt{x, y});
    }

    double orig_a = 3.14;
    double orig_b = 2.72;
    double orig_c = 4.0;
    double a = orig_a;
    double b = orig_b;
    double c = orig_c;

    auto f = [&a, &b, &c](double x) {
        return (a * sin(x) + b * log(x)) * (a * sin(x) + b * log(x)) + c * x * x;
    };

    sort(data.begin(), data.end(), [](auto lhs, auto rhs) {return lhs.x < rhs.x;});

    int cnt = 0;
    for (auto pt : data) {
        a = orig_a;
        b = orig_b;
        c = orig_c;
        double y = f(pt.x);
        double min_y = y;
        double max_y = y;
        for (int k_a = -1; k_a <= 1; k_a += 2)
            for (int k_b = -1; k_b <= 1; k_b += 2)
                for (int k_c = -1; k_c <= 1; k_c += 2) {
                    a = orig_a + k_a * 0.001;
                    b = orig_b + k_b * 0.001;
                    c = orig_c + k_c * 0.001;
                    if (f(pt.x) < min_y) {
                        min_y = f(pt.x);
                    }
                    if (f(pt.x) > max_y) {
                        max_y = f(pt.x);
                    }
                }
        if (pt.y < min_y || pt.y > max_y) {
            cout << pt.y << " out of [" << min_y << ", " << max_y << "] for " << pt.x << endl;
            ++cnt;
        }
    }
    cout << "cnt = " << cnt << endl;
    /*
    double ka = 0.00001;
    double kb = 0.00001;
    double kc = 0.000001;
    for (;;) {
        double de_da = 0.0;
        double de_db = 0.0;
        double de_dc = 0.0;
        double err = 0.0;
        for (auto& pt : data) {
            err += sqrt((f(pt.x) - pt.y) * (f(pt.x) - pt.y));
            de_da += 4 * (f(pt.x) - pt.y) * (a * sin(pt.x) + b * log(pt.x)) * sin(pt.x);
            de_db += 4 * (f(pt.x) - pt.y) * (a * sin(pt.x) + b * log(pt.x)) * log(pt.x);
            de_dc += 2 * (f(pt.x) - pt.y) * pt.x * pt.x;
        }
        cout << "err = " << err << endl;
        cout << "a = " << a << " b = " << b << " c = " << c << endl;
        string s;
        cin >> s;
        if (s == "exit") {
            break;
        }
        a -= ka * de_da;
        b -= kb * de_db;
        c -= kc * de_dc;
    }*/
    return 0;
}
