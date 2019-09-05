#include <cstdio>
#include <vector>
#include <iostream>
#include <bitset>
#include <iostream>
#include <sstream>

void printVector(const char* name, const std::vector<uint64_t> data)
{
  std::cout << name << " = ";
  for (auto x : data)
    std::cout << x << " ";
  std::cout << std::endl;
}

int main()
{
    std::cin.sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    if (n == 0 || m == 0)
    {
      printf("Yes");
      return 0;
    }
    std::vector<uint64_t> prev(m / 64 + 1, 0);
    std::vector<uint64_t> shifted_prev(m / 64  + 1, 0);
    std::vector<uint64_t> cur(m / 64 + 1, 0);
    std::vector<uint64_t> shifted_cur(m / 64 + 1, 0);
    std::vector<uint64_t> lor(prev.size(), 0);
    std::vector<uint64_t> shifted_lor(prev.size(), 0);
    std::vector<uint64_t> sum(prev.size(), 0);
    std::vector<uint64_t> shifted_sum(prev.size(), 0);
    const uint64_t max_val = (static_cast<uint64_t>(1) << 63);
    std::string s;
    getline(std::cin, s);
    for (int i = 0; i < n; ++i)
    {
//      std::cout << "Iteration ---- " << std::endl;
      getline(std::cin, s);
      std::stringstream ss(s);
      uint64_t mask = 0;
      for (int j = 0; j < m; ++j)
      {
        if (j % 64 == 0)
        {
          cur[j / 64] = 0;
          mask = max_val;
        }
        int x;
        ss >> x;
        if (x)
          cur[j / 64] |= mask;
        mask >>= 1;
      }
//      printVector("Prev", prev);
//      printVector("Cur", cur);
      for (size_t j = 0; j < cur.size(); ++j)
      {
        lor[j] = (cur[j] & prev[j]);
        sum[j] = (cur[j] ^ prev[j]);
      }
//      printVector("lor", lor);
//      printVector("sum", sum);
      for (size_t j = 0; j < cur.size(); ++j)
      {
        shifted_cur[j] = (cur[j] << 1);
        if (j + 1 < cur.size() && (cur[j + 1] & max_val))
        {
          shifted_cur[j] |= 1;
        }
        shifted_lor[j] = (shifted_cur[j] & shifted_prev[j]);
        shifted_sum[j] = (shifted_cur[j] ^ shifted_prev[j]);
      }
//      printVector("Shifted prev", shifted_prev);
//      printVector("Shifted cur", shifted_cur);
//      printVector("Shifted lor", shifted_lor);
//      printVector("Shifted sum", shifted_sum);
      for (size_t j = 0; j < cur.size(); ++j)
      {
        if (shifted_lor[j] & sum[j])
        {
          printf("No");
          return 0;
        }
        if (shifted_sum[j] & lor[j])
        {
          printf("No");
          return 0;
        }
      }
      prev.swap(cur);
      shifted_prev.swap(shifted_cur);
    }
    printf("Yes");
    return 0;
}
