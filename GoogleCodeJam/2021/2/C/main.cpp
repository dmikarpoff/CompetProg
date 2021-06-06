#include <iostream>
#include <vector>

using namespace std;

int n;
vector<char> used;

void gen(vector<int>& d, const vector<int> v, int depth, uint64_t& sum)
{
  if (depth == 0)
  {
      for (int i = 1; i <= n; ++i)
      {
          used[i] = 1;
          d.push_back(i);
          // cout << "--- First step = " << i << endl;
          gen(d, v, 1, sum);
          d.pop_back();
          used[i] = 0;
      }
      return;
  }
  // cout << "At depth " << depth << endl;
  /*
  if (depth == n)
  {
      for (auto x : d)
      {
          cout << x << " ";
      }
      cout << endl;
  }
  */
  if (depth == n)
  {
      ++sum;
      return;
  }
  if (v[depth - 1] != d.size())
  {
      return;
  }
  if (v[depth] == v[depth - 1] + 1)
  {
    for (int i = 1; i < d.back(); ++i)
    {
        if (used[i] == 0)
        {
            used[i] = 1;
            d.push_back(i);
            gen(d, v, depth + 1, sum);
            d.pop_back();
            used[i] = 0;
        }
    }
    return;
  }
  if (v[depth] > v[depth - 1])
  {
      return;
  }
  int to_pop = v[depth - 1] - v[depth] + 1;
  // cout << "There are " << to_pop << " elems to pop" << endl;
  if (to_pop > d.size())
  {
      return;
  }
  int from = d[d.size() - to_pop];
  // cout << "from = " << from << endl;
  int to = (d.size() < to_pop + 1 ? n + 1 : d[d.size() - to_pop - 1]);
  // cout << "to = " << to << endl;
  for (int i = from + 1; i < to; ++i)
  {
      if (!used[i])
      {
          used[i] = 1;
          vector<int> temp{d.end() - to_pop, d.end()};
          d.erase(d.end() - to_pop, d.end());
          d.push_back(i);
          gen(d, v, depth + 1, sum);
          d.pop_back();
          d.insert(d.end(), temp.begin(), temp.end());
          used[i] = 0;
      }
  }
}

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> v[i];
        }
        vector<int> temp;
        uint64_t sum = 0;
        used.assign(n + 1, 0);
        gen(temp, v, 0, sum);
        cout << "Case #" << o + 1 << ": ";
        cout << sum << endl;
    }
    return 0;
}
