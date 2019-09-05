#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <queue>
#include <algorithm>

using namespace std;

struct Point
{
  double x;
  double y;
};

double dist(Point a, Point b)
{
  double u = a.x - b.x;
  double v = a.y - b.y;
  return sqrt(u * u + v * v);
}

int main()
{
    double low_pace, high_pace;
    cin >> low_pace >> high_pace;
    int n;
    cin >> n;
    vector<Point> station(n + 2);
    for (size_t i = 1; i <= n; ++i)
      cin >> station[i].x >> station[i].y;
    vector<vector<double>> adj(n + 2, vector<double>(n + 2, -1.0));
    vector<vector<int>> p(n + 2, vector<int>(n + 2, -1));
    while (true)
    {
      int a, b;
      cin >> a >> b;
      if (a == 0 && b == 0)
        break;
      double l = dist(station[a], station[b]) / high_pace;
      adj[a][b] = l;
      adj[b][a] = l;
    }
    cin >> station.front().x >> station.front().y;
    cin >> station.back().x >> station.back().y;
    for (int i = 0; i < n + 2; ++i)
      for (int j = 0; j < n + 2; ++j)
    {
      if (i != j && adj[i][j] < -0.5)
      {
        double l = dist(station[i], station[j]) / low_pace;
        adj[i][j] = l;
      }
    }

    for (int k = 0; k < n + 2; ++k)
      for (int i = 0; i < n + 2; ++i)
        for (int j = 0; j < n + 2; ++j)
          if (i != j && i != k && j != k &&
              adj[i][k] + adj[k][j] < adj[i][j])
    {
      adj[i][j] = adj[i][k] + adj[k][j];
      p[i][j] = k;
    }
    cout << fixed << setprecision(6) << adj[0][n + 1] << endl;
    vector<pair<int, int>> st;
    st.push_back(make_pair(0, n + 1));
    vector<int> path;
    while (!st.empty())
    {
      auto edge = st.back();
      st.pop_back();
      int m = p[edge.first][edge.second];
      if (m == -1)
      {
        path.push_back(edge.second);
      }
      else
      {
        st.push_back(make_pair(edge.first, m));
        st.push_back(make_pair(m, edge.second));
      }
    }
    reverse(path.begin(), path.end());
    path.pop_back();
    cout << path.size() << " ";
    for (auto x : path)
      cout << x << " ";
    return 0;
}
