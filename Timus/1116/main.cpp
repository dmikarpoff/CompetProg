#include <iostream>
#include <vector>

using namespace std;

struct Segment
{
  int a, b;
  int val;
};

int main()
{
    int n;
    vector<Segment> f1;
    vector<Segment> f2;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
      int a, b, c;
      cin >> a >> b >> c;
      f1.push_back({a, b, c});
    }
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
      int a, b, c;
      cin >> a >> b >> c;
      f2.push_back({a, b, c});
    }

    size_t j = 0, i = 0;
    vector<Segment> res;
    while (i < f1.size())
    {
      if (j == f2.size())
      {
        res.push_back(f1[i]);
        ++i;
        continue;
      }
      if (f2[j].b <= f1[i].a)
      {
        ++j;
        continue;
      }
      if (f1[i].b <= f2[j].a)
      {
        if (f1[i].a < f1[i].b)
          res.push_back(f1[i]);
        ++i;
        continue;
      }
      if (f2[j].a > f1[i].a)
      {
        res.push_back({f1[i].a, f2[j].a, f1[i].val});
      }
      if (f2[j].b < f1[i].b)
      {
        f1[i].a = f2[j].b;
        ++j;
      }
      else
      {
        ++i;
      }
    }
    cout << res.size() << " ";
    for (const auto& s : res)
      cout << s.a << " " << s.b << " " << s.val << " ";
    return 0;
}
