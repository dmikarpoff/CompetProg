#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int o = 0; o < T; ++o)
    {
      int n, l;
      cin >> n >> l;
      vector<int64_t> dist0(n + 1, 200000);
      vector<int64_t> dist1(n + 1, 200000);
      int64_t cost = 200000;
      int64_t last_zero = n;
      int64_t last_one = -1;
      dist0[n] = 0;
      for (int64_t i = n - 1; i >= 0; --i)
      {
        if ((100 * i) % n == 0)
        {
          last_zero = i;
        }
        else if ((100 * i) % n >= (n % 2 == 0 ? n / 2 : n / 2 + 1))
        {
          last_one = i;
        }
        if (last_zero != -1)
          dist0[i] = last_zero - i;
        if (last_one != -1)
          dist1[i] = last_one - i;
      }
      vector<int> down;
      vector<int> neutral;
      int total = 0;
      int rem = n;
      for (int i = 0; i < l; ++i)
      {
        int val;
        cin >> val;
        rem -= val;
        if (dist1[val] == 0)
        {
          total += 100 * val / n + 1;
          continue;
        }
        if (dist0[val] == 0)
        {
          neutral.push_back(val);
        }
        else
          down.push_back(val);
      }
      std::sort(down.begin(), down.end(),
                [&dist1](int x, int y)
                {
                  return dist1[x] < dist1[y];
                });
      sort(neutral.begin(), neutral.end(),
           [&dist1](int x, int y)
            {
              return dist1[x] < dist1[y];
            });
      int additional = 0;
      size_t j = 0;
      size_t i = 0;
      while (i < down.size() && dist1[0] > dist1[down[i]])
      {
        if (dist1[down[i]] <= rem)
        {
          if (!neutral.empty() && j < neutral.size() - 1)
          {
            if (dist1[neutral[j]] + dist1[neutral[j + 1]] <
                dist1[down[i]])
            {
              rem -= dist1[neutral[j]] + dist1[neutral[j + 1]];
              neutral[j] += dist1[neutral[j]];
              neutral[j + 1] += dist1[neutral[j + 1]];
              j += 2;
              continue;
            }
          }
          rem -= dist1[down[i]];
          down[i] += dist1[down[i]];
          ++i;
        }
        else
        {
          break;
        }
      }
      if (!neutral.empty())
      {
        while (j < neutral.size() - 1)
        {
          if (dist1[neutral[j]] + dist1[neutral[j + 1]] < dist1[0])
          {
              if (rem < dist1[neutral[j]] + dist1[neutral[j + 1]])
                break;
              rem -= dist1[neutral[j]] + dist1[neutral[j + 1]];
              neutral[j] += dist1[neutral[j]];
              neutral[j + 1] += dist1[neutral[j + 1]];
              j += 2;
              continue;
          }
          if (dist1[0] > rem)
            break;
          rem -= dist1[0];
          additional++;
        }
      }

      std::sort(down.begin() + i, down.end(),
                [&dist0](int x, int y)
                {
                  return dist0[x] < dist0[y];
                });
      while (i < down.size() || j < neutral.size())
      {
        if (i < down.size() && dist0[down[i]] < rem &&
            (j == neutral.size() || dist0[down[i]] <
                                    dist1[neutral[j]]))
        {
          rem -= dist0[down[i]];
          down[i] += dist0[down[i]];
          ++i;
          continue;
        }
        if (j < neutral.size() && dist1[neutral[j]] < rem)
        {
          rem -= dist1[neutral[j]];
          neutral[j] += dist1[neutral[j]];
          ++j;
          continue;
        }
        break;
      }

      for (auto x : down)
        total += static_cast<int>(100.0 * x / n + 0.5);
      for (auto x : neutral)
        total += static_cast<int>(100.0 * x / n + 0.5);
      total += static_cast<int>(100.0 * rem / n + 0.5);
      total += additional * static_cast<int>(100.0 * dist1[0] / n + 0.5);
//      cout << rem << endl;
      cout << "Case #" << o + 1 << ": ";
      cout << total << endl;
    }
    return 0;
}
