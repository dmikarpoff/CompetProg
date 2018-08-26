#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class BigInteger
{
public:
  BigInteger(int x)
  {
    while (x > 0)
    {
      data.push_back(x % 10);
      x /= 10;
    }
  }
  void print() const
  {
    for (size_t i = data.size() - 1; i != -1; --i)
      cout << data[i];
  }

  BigInteger& operator++()
  {
    data[0]++;
    for (size_t i = 0; data[i] > 9; ++i)
    {
      if (i == data.size() - 1)
        data.push_back(0);
      data[i + 1]++;
      data[i] = data[i] % 10;
    }
    return *this;
  }
  friend BigInteger operator*(const BigInteger& lhs,
                              const BigInteger& rhs)
  {
    BigInteger res(0);
    res.data.resize(lhs.data.size() + rhs.data.size() + 2, 0);
    for (size_t i = 0; i < lhs.data.size(); ++i)
      for (size_t j = 0; j < rhs.data.size(); ++j)
        res.data[i + j] += lhs.data[i] * rhs.data[j];
    for (size_t i = 0; i < res.data.size() - 1; ++i)
    {
      res.data[i + 1] += res.data[i] / 10;
      res.data[i] %= 10;
    }
    assert(res.data.back() < 10);
    while (res.data.back() == 0)
      res.data.pop_back();
    return res;
  }

private:
  vector<int> data;
};

int main()
{
    int n;
    cin >> n;
    BigInteger a(1);
    BigInteger b(2);
    for (int i = 0; i < n; ++i)
    {
      b.print();
      cout << endl;
      if (i == n - 1)
        break;
      a = a * b;
      b = a;
      ++b;
    }
    return 0;
}
