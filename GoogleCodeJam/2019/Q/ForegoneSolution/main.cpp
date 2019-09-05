#include <iostream>
#include <string>
#include <sstream>

using namespace std;

std::string to_str(int v) {
  stringstream ss;
  ss << v;
  return ss.str();
}

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o) {
      std::string n;
      cin >> n;
      string lhs, rhs;
      for (size_t i = 0; i < n.size(); ++i) {
        if (i == 0 && n[0] == '1') {
          int v = (n[0] - '0') * 10 + n[1] - '0';
          lhs = to_str(v / 2);
          rhs = to_str(v - v / 2);
          ++i;
        } else {
          if (n[i] > '6') {
            lhs += '6';
            rhs += n[i] - 6;
          } else {
            int v = n[i] - '0';
            lhs += to_str(v / 2);
            rhs += to_str(v - v / 2);
          }
        }
      }
      cout << "Case #" << o + 1 << ": ";
      cout << lhs << " " << rhs << endl;
    }
    return 0;
}
