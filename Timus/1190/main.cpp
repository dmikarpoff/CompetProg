#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> p(n, -1);
    for (size_t i = 0; i < p.size(); ++i)
    {
      string s;
      cin >> s;
      int x;
      cin >> x;
      if (x == 1)
        cin >> p[i];
    }
    vector<int> ma(p.begin(), p.end());
    vector<int> mi(p.begin(), p.end());
    if (mi.back() == -1)
      mi.back() = 1;
    size_t i = mi.size() - 2;
    while (i != -1)
    {
      if (mi[i] == -1)
        mi[i] = mi[i + 1];
      --i;
    }

    if (accumulate(mi.begin(), mi.end(), 0) > 10000)
    {
      cout << "NO";
      return 0;
    }
    if (ma.front() == -1)
      ma.front() = 10000;
    for (size_t i = 1; i < ma.size(); ++i)
    {
      if (ma[i] == -1)
        ma[i] = ma[i - 1];
    }
    if (accumulate(ma.begin(), ma.end(), 0) < 10000)
      cout << "NO";
    else
      cout << "YES";
    return 0;
}
