#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o) {
      int n; cin >> n;
      string s; cin >> s;
      transform(s.begin(), s.end(), s.begin(),
                [](char c) { return c == 'E' ? 'S' : 'E';});
      printf("Case #%d: %s\n", o + 1, s.c_str());
    }
    return 0;
}
