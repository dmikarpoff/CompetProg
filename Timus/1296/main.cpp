#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int64_t res = 0;
    int64_t min_prefix = 0;
    int64_t prefix = 0;
    for (int i = 0; i < n; ++i)
    {
      int v;
      cin >> v;
      prefix += v;
      if (prefix < min_prefix)
        min_prefix = prefix;
      if (prefix - min_prefix > res)
        res = prefix - min_prefix;
    }
    cout << res;
    return 0;
}
