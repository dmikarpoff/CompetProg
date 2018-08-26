#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point2D
{
    double x;
    double y;
};

constexpr double pi = 2 * acos(0.0);
constexpr double da = pi / 10000.0;

double estSquare(const std::vector<Point2D>& pts)
{
    double res = 0.0;
    for (size_t i = 0; i < pts.size() - 1; ++i)
    {
        Point2D u{pts[i].x - pts[0].x, pts[i].y - pts[0].y};
        Point2D v{pts[i + 1].x - pts[0].x, pts[i + 1].y - pts[0].y};
        res += abs(u.x * v.y - u.y * v.x);
    }
    return 0.5 * res;
}

int main()
{
    int n;
    cin >> n;
    vector<Point2D> pts(n);
    for (int i = 0; i < n; ++i)
        cin >> pts[i].x >> pts[i].y;

    double min_len = 1E+30;
    double s = estSquare(pts);
    if (s < 1E-6)
    {
      cout << 0.0;
      return 0;
    }

    for (double a = 0.0; a < pi; a += da)
    {
        bool debug = false;//(abs(a - 3 * pi / 2.0) < 1E-6);
        vector<double> prj(n, 0.0);
        for (size_t j = 0; j < n; ++j)
          prj[j] = pts[j].x * cos(a) - pts[j].y * sin(a);
        double min_x = 1E+30, max_x = -1E+30;
        size_t min_x_idx = -1;
        for (size_t i = 0; i < n; ++i)
        {
            if (prj[i] < min_x)
            {
              min_x = prj[i];
              min_x_idx = i;
            }
            max_x = max(max_x, prj[i]);
        }

        double left_s = 0.0;
        Point2D mid_a, mid_b;
        do
        {
//          cout << "min_x = " << min_x << " max_x = " << max_x << endl;
          double cur_x = 0.5 * (min_x + max_x);
//          cout << "cur_x = " << cur_x << endl;
          std::vector<Point2D> left_poly;
          left_poly.push_back(pts[min_x_idx]);
          size_t i = min_x_idx;
          while (prj[(i + 1) % n] < cur_x)
          {
            i = (i + 1) % n;
            left_poly.push_back(pts[i]);
          }
          int l_idx = i;
          int r_idx = (i + 1) % n;
          Point2D l_pt = pts[l_idx];
          Point2D r_pt = pts[r_idx];
          double k = (cur_x - prj[l_idx]) / (prj[r_idx] - prj[l_idx]);
//          if (debug)
//          {
//            cout << i << "; " << k << endl;
//          }
          mid_a = {l_pt.x + k * (r_pt.x - l_pt.x),
                   l_pt.y + k * (r_pt.y - l_pt.y)};
          left_poly.push_back(mid_a);
          while (prj[(i + 1) % n] >= cur_x)
            i = (i + 1) % n;
          l_idx = i;
          r_idx = (i + 1) % n;
          l_pt = pts[i];
          r_pt = pts[(i + 1) % n];
          k = (cur_x - prj[l_idx]) / (prj[r_idx] - prj[l_idx]);
          if (debug)
          {
            cout << i << "; " << k << endl;
          }
          mid_b = {l_pt.x + k * (r_pt.x - l_pt.x),
                   l_pt.y + k * (r_pt.y - l_pt.y)};
          left_poly.push_back(mid_b);
          i = (i + 1) % n;
          left_poly.push_back(pts[i]);
          while (i != min_x_idx)
          {
            i = (i + 1) % n;
            left_poly.push_back(pts[i]);
          }
          left_s = estSquare(left_poly);
          if (2.0 * left_s < s)
            min_x = cur_x;
          else
            max_x = cur_x;
          if (abs(2.0 * left_s - s) < 1E-8 && debug)
          {
            for (auto p : left_poly)
              cout << "(" << p.x << "," << p.y << ") ";
            cout << endl;
          }
//          cout << "Squares: " << left_s << " " << s << endl;
//          char symb;
//          cin >> symb;
        }
        while (abs(2.0 * left_s - s) > 1E-8);
        if (debug)
        {
          cout << mid_a.x << " " << mid_a.y << endl;
          cout << mid_b.x << " " << mid_b.y << endl;
        }
        double l = hypot(mid_a.x - mid_b.x, mid_a.y - mid_b.y);
        if (l < min_len)
        {
          min_len = l;
//          cout << "Split with l = " << l << ", cur_x = "
//               << mid_a.x << ", a = " << a << endl;
        }
    }
    cout.setf(ios::fixed);
    cout.precision(4);
    cout << min_len << endl;
    return 0;
}
