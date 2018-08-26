#include <iostream>
#include <vector>
#include <string>
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

  BigInteger operator+(const BigInteger& other) const
  {
    BigInteger res;
    res.digit.resize(max(digit.size(), other.digit.size()), 0);
    copy(digit.begin(), digit.end(), res.digit.begin());
    transform(other.digit.begin(), other.digit.end(),
              res.digit.begin(), res.digit.begin(),
              [](int a, int b) {return a + b;});
    res.normalize();
    return res;
  }

  BigInteger operator/(int x) const
  {
    BigInteger res;
    res.digit.resize(digit.size(), 0);
    int t = 0;
    for (size_t i = digit.size() - 1; i != -1; --i)
    {
      t = t * 10 + digit[i];
      res.digit[i] = t / x;
      t %= x;
    }
    res.normalize();
    return res;
  }

  bool operator!=(const BigInteger& other) const
  {
    if (digit.size() != other.digit.size())
      return true;
    for (size_t i = 0; i < digit.size(); ++i)
      if (digit[i] != other.digit[i])
        return true;
    return false;
  }
  bool operator==(const BigInteger& other) const
  {
    return !(*this != other);
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
  string str;
  cin >> str;
  BigInteger sum(str);
  sum = sum * BigInteger("2");
  string left_str = "1";
  string right_str = "1";
  right_str.resize(601, '0');
  BigInteger left(left_str), right(right_str);
  while (true)
  {
//    cout << "Left = " << left.toString() << endl;
//    cout << "Right = " << right.toString() << endl;
    BigInteger mid = (left + right) / 2;
//    cout << "Mid = " << mid.toString() << endl;
    BigInteger est = mid * (mid + BigInteger("1"));
    if (est == sum)
    {
      cout << mid.toString() << endl;
      return 0;
    }
    if (est > sum)
      right = move(mid);
    else
      left = move(mid);
//    char c;
//    cin >> c;
  }
  return 0;
}
