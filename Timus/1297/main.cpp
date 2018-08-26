#include <iostream>

using namespace std;

int main()
{
    string s;
    cin >> s;
    size_t first = 0, last = 0;
    size_t max_len = 1;
    for (int i = 1; i < s.size(); ++i)
    {
      if (s[i] == s[i - 1])
      {
        int j = i - 1;
        int h = i;
        while (j - 1 >= 0 && h + 1 < s.size() &&
               s[j - 1] == s[h + 1])
        {
          --j;
          ++h;
        }
        if (h - j + 1 > max_len)
        {
          max_len = h - j + 1;
          first = j;
          last = h;
        }
      }
      int j = i;
      int h = i;
      while (j - 1 >= 0 && h + 1 < s.size() &&
               s[j - 1] == s[h + 1])
      {
        --j;
        ++h;
      }
      if (h - j + 1 > max_len)
      {
        max_len = h - j + 1;
        first = j;
        last = h;
      }
    }
    ++last;
    cout << string(s.begin() + first, s.begin() + last);
    return 0;
}
