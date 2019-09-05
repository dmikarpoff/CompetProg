#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
  int x;
  int y;
  int idx;
};

int main()
{
    int n;
    cin >> n;
    vector<Point> pt(n);
    for (size_t i = 0; i < n; ++i)
    {
      cin >> pt[i].x >> pt[i].y;
      pt[i].idx = i + 1;
    }
    for (size_t i = 0; i < n; ++i)
    {
      if (pt[i].x < pt[0].x || (pt[0].x == pt[i].x &&
                                pt[i].y < pt[0].y))
        swap(pt[i], pt[0]);
    }
    Point p = pt.front();
    sort(pt.begin() + 1, pt.end(),
         [&p](const Point& lhs, const Point& rhs)
         {
            Point dl{lhs.x - p.x, lhs.y - p.y};
            Point dr{rhs.x - p.x, rhs.y - p.y};
            return atan2(dl.x, dl.y) < atan2(dr.x, dr.y);
         });
    cout << pt[0].idx << " " << pt[pt.size() / 2].idx << endl;
    return 0;
}
