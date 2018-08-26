#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int k;
    cin >> k;
    vector<int> res;
    res.push_back(6);
    res.push_back(3);
    for (int i = 0; i < k - 1; ++i)
    {
      for (size_t j = 0; j < res.size(); ++j)
        res[j] *= 55;
      for (size_t j = 0; j < res.size() - 1; ++j)
      {
        res[j + 1] += res[j] / 10;
        res[j] = res[j] % 10;
      }
      while (res.back() > 10)
      {
        int t = res.back() / 10;
        res.back() %= 10;
        res.push_back(t);
      }
    }
    for (auto i = res.rbegin(); i != res.rend(); ++i)
      cout << *i;
    return 0;
}
