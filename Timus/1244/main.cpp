#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct Elem {
  int value;
  int status;
  int parent;
  size_t idx;
};

int main()
{
    int sum;
    cin >> sum;
    int n;
    cin >> n;
    vector<Elem> current, next;
    vector<Elem> to_append;
    int total_sum = 0;
    for (int i = 0; i < n; ++i) {
      int w;
      cin >> w;
      total_sum += w;
      to_append.push_back(Elem{w, 0, -1, i});
      for (const auto e : current) {
        Elem u{e.value + w, e.status, e.value, i};
        to_append.push_back(u);
      }
      size_t i_cur = 0;
      size_t i_app = 0;
      while (i_cur != current.size() || i_app != to_append.size()) {
        if (i_cur == current.size() ||
              (i_app < to_append.size() && to_append[i_app].value < current[i_cur].value)) {
          if (next.empty() ||
                next.back().value != to_append[i_app].value) {
            next.push_back(to_append[i_app]);
          } else {
            next.back().status = -1;
          }
          ++i_app;
          continue;
        }
        if (next.empty() ||
              next.back().value != current[i_cur].value) {
          next.push_back(current[i_cur]);
        } else {
          next.back().status = -1;
        }
        ++i_cur;
      }
      swap(current, next);
      next.clear();
      to_append.clear();
    }
    sum = total_sum - sum;
    auto it = lower_bound(current.begin(), current.end(), sum,
                [](const Elem& lhs, int s) {
                  return lhs.value < s;
                });
    /*
    for (const auto& e : current) {
      cout << e.value << " " << e.status << " " << e.parent
           << " " << e.idx << endl;
    }
    */
    if (it == current.end() || it->value != sum) {
      cout << 0 << endl;
      return 0;
    }
    if (it->status == -1) {
      cout << -1 << endl;
      return 0;
    }
    vector<size_t> res;
    while (true) {
      res.push_back(it->idx);
      if (it->parent == -1)
        break;
      sum = it->parent;
      it = lower_bound(current.begin(), current.end(), sum,
                [](const Elem& lhs, int s) {
                  return lhs.value < s;
                });
      assert(it->value == sum);
    }
    reverse(res.begin(), res.end());
    for (auto t : res)
      cout << t + 1 << " ";
    cout << endl;
    return 0;
}
