#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
      int k;
      cin >> k;
      for (int j = 0; j < k; ++j) {
        int v;
        cin >> v;
        adj[i].push_back(--v);
      }
    }
    vector<int> mark(n, 0);
    bool smth_changed = true;
    while (smth_changed) {
      smth_changed = false;
      for (int i = 0; i < n; ++i) {
        int enemies = 0;
        for (auto e : adj[i]) {
          if (mark[i] == mark[e])
            enemies++;
        }
        if (enemies > 1) {
//          cout << "Move " << i + 1 << " from " << mark[i] << endl;
          mark[i] = 1 - mark[i];
          smth_changed = true;
        }
      }
    }
    vector<int> a, b;
    for (int i = 0; i < n; ++i) {
      if (mark[i] == 0)
        a.push_back(i + 1);
      else
        b.push_back(i + 1);
    }
    if (b.size() < a.size() || (b.size() == a.size() && b.front() == 1))
      swap(a, b);
    cout << a.size() << endl;
    for (auto v : a)
      cout << v << ' ';
    cout << endl;
    return 0;
}
