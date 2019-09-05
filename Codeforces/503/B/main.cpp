#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (size_t i = 1; i <= n; ++i)
      cin >> p[i];
    for (int i = 1; i <= n; ++i)
    {
      vector<char> used(n + 1, 0);
      int v = i;
      do
      {
        used[v] = 1;
        v = p[v];
      }
      while (used[v] == 0);
      cout << v << " ";
    }
    return 0;
}
