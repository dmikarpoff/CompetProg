#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

enum class Edge
{
  kFront = 0,
  kRight,
  kLeft,
  kBack,
  kTop,
  kBottom
};

Edge opposite(Edge e)
{
  switch (e)
  {
  case Edge::kFront:
    return Edge::kBack;
  case Edge::kBack:
    return Edge::kFront;
  case Edge::kLeft:
    return Edge::kRight;
  case Edge::kRight:
    return Edge::kLeft;
  case Edge::kTop:
    return Edge::kBottom;
  case Edge::kBottom:
    return Edge::kTop;
    return Edge::kBottom;
  }
}

std::pair<string, string> extract(const string& cube, Edge e)
{
  string p1, p2;
  switch (e)
  {
    case Edge::kFront:
      p1 = p1 + cube[static_cast<int>(Edge::kLeft)];
      p1 = p1 + cube[static_cast<int>(Edge::kRight)];
      p2 = p2 + cube[static_cast<int>(Edge::kTop)];
      p2 = p2 + cube[static_cast<int>(Edge::kBottom)];
      break;
    case Edge::kTop:
      p1 = p1 + cube[static_cast<int>(Edge::kLeft)];
      p1 = p1 + cube[static_cast<int>(Edge::kRight)];
      p2 = p2 + cube[static_cast<int>(Edge::kFront)];
      p2 = p2 + cube[static_cast<int>(Edge::kBack)];
      break;
    case Edge::kLeft:
      p1 = p1 + cube[static_cast<int>(Edge::kTop)];
      p1 = p1 + cube[static_cast<int>(Edge::kBottom)];
      p2 = p2 + cube[static_cast<int>(Edge::kFront)];
      p2 = p2 + cube[static_cast<int>(Edge::kBack)];
      break;
  }
  if (p1[0] < p1[1])
    swap(p1[0], p1[1]);
  if (p2[0] < p2[1])
    swap(p2[0], p2[1]);

  if (p1 < p2)
    swap(p1, p2);
  return {p1, p2};
}

using pair_ss = pair<string, string>;

int main()
{
    int n;
    cin >> n;
    vector<string> cubes;
    cubes.reserve(n);
    array<Edge, 3> var = {Edge::kFront, Edge::kLeft, Edge::kTop};
    vector<pair_ss> descr[3];
    for (int i = 0; i < n; ++i)
    {
      string s;
      cin >> s;
      cubes.push_back(s);
      for (size_t j = 0; j < 3; ++j)
        descr[j].push_back(extract(s, var[j]));
    }
    int res = 1;
    for (int i = 0; i < n - res; ++i)
    {
//      cout << "i: " << i << endl;
      for (size_t e = 0; e < 3; ++e)
      {
        int cnt = 1;
        const auto& q = descr[e][i];
//        cout << "Query: " << q.first << " " << q.second << endl;
        for (size_t j = i + 1; j < n; ++j)
          for (size_t e1 = 0; e1 < 3; ++e1)
          {
            auto c = descr[e1][j];
            if (c == q)
            {
              cnt++;
              break;
            }
          }
        if (cnt > res)
          res = cnt;
      }
    }
    cout << res;
    return 0;
}
