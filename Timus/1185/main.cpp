#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point
{
  int x;
  int y;
};

Point operator-(const Point& lhs, const Point& rhs)
{
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}

int cross(const Point& prev, const Point& cur,
          const Point& next)
{
  auto u = cur - prev;
  auto v = next - prev;
  return u.x * v.y - u.y * v.x;
}

int main()
{
    int n, l;
    cin >> n >> l;
    vector<Point> v;
    for (int i = 0; i < n; ++i)
    {
      int x, y;
      cin >> x >> y;
      v.push_back({x, y});
    }
    auto cmp = [](const Point& lhs, const Point& rhs)
    {
      return (lhs.x < rhs.x || (lhs.x == rhs.x &&
                                lhs.y < rhs.y));
    };
    sort(v.begin(), v.end(), cmp);

    vector<Point> upper(1, v[0]);
    vector<Point> lower(1, v[0]);
    for (size_t i = 1; i < v.size(); ++i)
    {
      if (i == v.size() - 1 ||
            cross(v.front(), v.back(), v[i]) >= 0)
      {
          while (upper.size() > 1 &&
                    cross(upper[upper.size() - 2],
                          upper[upper.size() - 1], v[i]) >= 0)
            upper.pop_back();
          upper.push_back(v[i]);
      }
      if (i == v.size() - 1 ||
            cross(v.front(), v.back(), v[i]) < 0)
      {
          while (lower.size() > 1 &&
                    cross(lower[lower.size() - 2],
                          lower[lower.size() - 1], v[i]) <
                  0)
            lower.pop_back();
          lower.push_back(v[i]);
      }
    }

    vector<Point> convex_hull(upper.begin(), upper.end());
    convex_hull.insert(convex_hull.end(), lower.rbegin() + 1,
                       lower.rend());
    /*
    cout << "-----------------------" << endl;
    for (auto pt : convex_hull)
    {
      cout << pt.x << " " << pt.y << endl;
    }
    */
    double res = 2.0 * 3.1415926536 * l;
    for (size_t i = 0; i < convex_hull.size() - 1; ++i)
    {
      auto s = convex_hull[i + 1] - convex_hull[i];
      res += sqrt(s.x * s.x + s.y * s.y);
    }

    cout << static_cast<int>(res + 0.5);

    return 0;
}
