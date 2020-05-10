#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int64_t x;
    int64_t y;
};

int main()
{
    int n;
    cin >> n;
    vector<Point> pt(n);
    size_t left = 0, right = 0;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> pt[i].x >> pt[i].y;
        if (pt[i].x < pt[left].x || (pt[i].x == pt[left].x && pt[i].y < pt[left].y))
        {
            left = i;
        }
        if (pt[i].x > pt[right].x || (pt[i].x == pt[right].x && pt[i].y > pt[right].y))
        {
            right = i;
        }
    }
    int64_t a = pt[left].y - pt[right].y;
    int64_t b = pt[right].x - pt[left].x;
    int64_t c = - a * pt[left].x - b * pt[left].y;
    vector<size_t> upper, lower;
    for (size_t i = 0; i < pt.size(); ++i) {
        if (i == left || i == right)
            continue;
        if (a * pt[i].x + b * pt[i].y + c > 0)
        {
            upper.push_back(i);
        }
        else
        {
            lower.push_back(i);
        }
    }
    if (upper.size() < lower.size())
    {
        swap(upper, lower);
    }
    int position = upper.size() - (n - 3) / 2 - 1;
    vector<pair<double, size_t>> order;
    const auto& l = pt[left];
    const auto& r = pt[right];
    for (auto i : upper)
    {
        const auto& p = pt[i];
        Point u{l.x - p.x, l.y - p.y};
        Point v{r.x - p.x, r.y - p.y};
        double cos = static_cast<double>(u.x * v.x + u.y * v.y) /
                     sqrt(u.x * u.x + u.y * u.y) / sqrt(v.x * v.x + v.y * v.y);
        order.push_back({cos, i});
    }
    nth_element(order.begin(), order.begin() + position, order.end());
    position = order[position].second;
    cout << pt[left].x << " " << pt[left].y << endl;
    cout << pt[right].x << " " << pt[right].y << endl;
    cout << pt[position].x << " " << pt[position].y << endl;
    return 0;
}
