#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class BigInteger
{
 public:
  explicit BigInteger(const string& str) : digit(str.size(), 0)
  {
    transform(str.rbegin(), str.rend(), digit.begin(),
              [](char c) { return static_cast<int>(c - '0');});
  }
  BigInteger(int x)
  {
    digit.push_back(x);
    normalize();
  }

  BigInteger operator*(const BigInteger& other) const
  {
    BigInteger res;
    res.digit.resize(digit.size() + other.digit.size(), 0);
    for (size_t i = 0; i < digit.size(); ++i)
      for (size_t j = 0; j < other.digit.size(); ++j)
        res.digit[i + j] += digit[i] * other.digit[j];
    res.normalize();
    return res;
  }

  string toString() const
  {
    string res;
    for (auto i = digit.rbegin(); i != digit.rend(); ++i)
      res += static_cast<char>(*i + '0');
    return res;
  }

  bool operator>(const BigInteger& other) const
  {
    if (digit.size() > other.digit.size())
      return true;
    if (digit.size() < other.digit.size())
      return false;
    for (size_t i = digit.size() - 1; i != -1; --i)
    {
      if (digit[i] > other.digit[i])
        return true;
      if (digit[i] < other.digit[i])
        return false;
    }
    return false;
  }

 private:
  BigInteger() {}

  void normalize()
  {
    for (size_t i = 0; i < digit.size() - 1; ++i)
    {
      digit[i + 1] += digit[i] / 10;
      digit[i] %= 10;
    }
    while (digit.back() > 9)
    {
      int t = digit.back() / 10;
      digit.back() %= 10;
      digit.push_back(t);
    }
    while (digit.size() > 0 && digit.back() == 0)
      digit.pop_back();
    if (digit.size() == 0)
      digit.push_back(0);
  }
  vector<int> digit;
};

int main()
{
    int n;
    cin >> n;
    if (n == 1)
    {
      cout << 1 << endl;
      return 0;
    }
    int num_2 = 0;
    int num_3 = 0;
    if (n % 3 ==0)
    {
      num_3 = n / 3;
    }
    else if (n % 3 == 1)
    {
      num_3 = (n - 4) / 3;
      num_2 = 2;
    }
    else
    {
      num_2 = 1;
      num_3 = (n - 2) / 3;
    }
    BigInteger res("1");
    for (int i = 0; i < num_2; ++i)
      res = res * BigInteger("2");
    for (int i = 0; i < num_3; ++i)
      res = res * BigInteger("3");
    cout << res.toString() << endl;
      res = res * BigInteger("3");
    return 0;
}
