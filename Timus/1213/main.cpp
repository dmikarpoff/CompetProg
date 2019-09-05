#include <iostream>
#include <cassert>
#include <string>
#include <set>

using namespace std;

int main()
{
    string gateway;
    getline(cin, gateway);
    string s;
    set<string> v;
    v.insert(gateway);
    do
    {
      getline(cin, s);
      if (s == "#")
        break;
      auto hyp_pos = s.find('-');
      string a(s.begin(), s.begin() + hyp_pos);
      string b(s.begin() + hyp_pos + 1, s.end());
      v.insert(a);
      v.insert(b);
    }
    while (true);
    cout << v.size() - 1;
    return 0;
}
