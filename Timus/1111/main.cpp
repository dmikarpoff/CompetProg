#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
  double x;
  double y;

  Point& operator-=(const Point& pt);
  double abs() const
  {
    return sqrt(x * x + y * y);
  }
};

Point operator+(const Point& lhs, const Point& rhs)
{
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Point operator-(const Point& lhs, const Point& rhs)
{
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}

Point operator*(double k, const Point& pt)
{
  return {k * pt.x, k * pt.y};
}

Point& Point::operator-=(const Point& pt)
{
  *this = *this - pt;
  return *this;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<Point, Point>> squares;
    for (int i = 0; i < n; ++i)
    {
      Point a, b;
      cin >> a.x >> a.y >> b.x >> b.y;
      squares.push_back(make_pair(a, b));
    }
    Point q;
    cin >> q.x >> q.y;
    vector<pair<int, double>> dist;
    for (size_t i = 0; i < squares.size(); ++i)
    {
//      cout << i << endl;
      Point pt = q;
      Point left = squares[i].first;
      Point right = squares[i].second;
      if ((left - right).abs() < 1E-3)
      {
        dist.push_back(make_pair(i + 1, (left - pt).abs()));
        continue;
      }
      Point mid = 0.5 * (left + right);
      pt -= mid;
      left -= mid;
      right -= mid;
//      cout << mid.x << " " << mid.y << endl;
      double l = left.abs();
//      cout << "l = " << l << endl;
      double sin_a = (left.x - left.y) / l / sqrt(2);
      double cos_a = (left.x + left.y) / l / sqrt(2);
//      cout << "left = " << left.x << ", " << left.y << endl;
//      cout << "cos_a = " << cos_a << endl;
//      cout << "sin_a = " << sin_a << endl;
//      cout << "pt = " << pt.x << ", " << pt.y << endl;
      auto temp = Point{cos_a * pt.x - sin_a * pt.y,
                        sin_a * pt.x + cos_a * pt.y};
      pt = temp;
//      cout << "rotated pt " << pt.x << ", " << pt.y << endl;
      pt.x = std::abs(pt.x);
      pt.y = std::abs(pt.y);
//      cout << "rotated pt " << pt.x << ", " << pt.y << endl;
      l /= sqrt(2);
      if (pt.x <= l && pt.y <= l)
      {
        dist.push_back(make_pair(i + 1, 0.0));
        continue;
      }
      if (pt.x <= l)
      {
        dist.push_back(make_pair(i + 1, pt.y - l));
      }
      else if (pt.y <= l)
      {
        dist.push_back(make_pair(i + 1, pt.x - l));
      }
      else
      {
        auto dp = pt - Point{l, l};
        dist.push_back(make_pair(i + 1, dp.abs()));
      }
    }
    stable_sort(dist.begin(), dist.end(),
                [](const pair<int, double>& x,
                   const pair<int, double>& y)
                {
                  return x.second + 1E-14 < y.second;
                });
    for (auto& x : dist)
      cout << x.first << " "/* << x.second << endl*/;
    return 0;
}
