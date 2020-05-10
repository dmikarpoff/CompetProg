#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Node {
    Node* parent = nullptr;
    char p_symb = 0;
    Node* link = nullptr;
    map<char, shared_ptr<Node>> transition;
    bool terminal = false;
    int id = -1;
};

class BigInteger
{
    static const uint64_t kModulo = 1000000000;
    static const uint64_t kWidth = 9;
 public:
  explicit BigInteger(int x)
  {
    if (x > 0) {
        digit.push_back(x);
        normalize();
    }
  }
  BigInteger(const BigInteger&) = default;
  BigInteger(BigInteger&&) = default;
  BigInteger& operator=(const BigInteger&) = default;
  BigInteger& operator=(BigInteger&&) = default;
  ~BigInteger() = default;

  BigInteger operator*(const BigInteger& other) const
  {
    BigInteger res(0);
    if (isZero() || other.isZero())
        return res;
    res.digit.resize(digit.size() + other.digit.size(), 0);
    for (size_t i = 0; i < digit.size(); ++i)
      for (size_t j = 0; j < other.digit.size(); ++j)
        res.digit[i + j] += digit[i] * other.digit[j];
    res.normalize();
    return res;
  }
  BigInteger operator*(int other) const
  {
      BigInteger res(*this);
      for (size_t i = 0; i < res.digit.size(); ++i)
        res.digit[i] *= other;
      res.normalize();
      return res;
  }

  BigInteger operator+(const BigInteger& other) const
  {
    if (other.isZero())
        return *this;
    if (isZero())
        return other;
    BigInteger res;
    res.digit.resize(max(digit.size(), other.digit.size()), 0);
    copy(digit.begin(), digit.end(), res.digit.begin());
    transform(other.digit.begin(), other.digit.end(),
              res.digit.begin(), res.digit.begin(),
              [](uint64_t a, uint64_t b) {return a + b;});
    res.normalize();
    return res;
  }
  BigInteger& operator+=(const BigInteger& other)
  {
      if (other.isZero())
        return *this;
      digit.resize(max(digit.size(), other.digit.size()));
      for (int i = 0; i < min(digit.size(), other.digit.size()); ++i)
        digit[i] += other.digit[i];
      normalize();
      return *this;
  }

  BigInteger operator/(int x) const
  {
    BigInteger res;
    res.digit.resize(digit.size(), 0);
    uint64_t t = 0;
    for (size_t i = digit.size() - 1; i != -1; --i)
    {
      t = t * kModulo + digit[i];
      res.digit[i] = t / x;
      t %= x;
    }
    res.normalize();
    return res;
  }

  bool isZero() const
  {
      return digit.empty() || (digit.size() == 1 && digit.front() == 0);
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
    if (digit.empty())
    {
        return "0";
    }
    stringstream res;
    res << *digit.rbegin();
    for (auto i = digit.rbegin() + 1; i != digit.rend(); ++i)
      res << setfill('0') << setw(kWidth) << *i;
    return res.str();
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
  BigInteger() = default;
  void normalize()
  {
    if (digit.empty())
        return;
    for (size_t i = 0; i < digit.size() - 1; ++i)
    {
      digit[i + 1] += digit[i] / kModulo;
      digit[i] %= kModulo;
    }
    while (digit.back() >= kModulo)
    {
      int t = digit.back() / kModulo;
      digit.back() %= kModulo;
      digit.push_back(t);
    }
    while (digit.size() > 0 && digit.back() == 0)
      digit.pop_back();
    if (digit.size() == 0)
      digit.push_back(0);
  }
  vector<uint64_t> digit;
};


static int node_num = 0;

using vvi = std::vector<std::vector<int>>;
using vv_big = vector<vector<BigInteger>>;

template <class T, class U>
T mult(const T& lhs, const U& rhs)
{
    vv_big res(lhs.size(), vector<BigInteger>(lhs.size(), BigInteger(0)));
    int n = lhs.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int h = 0; h < n; ++h)
                res[i][j] += lhs[i][h] * rhs[h][j];
    return res;
}

int main()
{
    set<int> terminal;
    int n, m, p;
    cin >> n >> m >> p;
    string abc, temp;
    getline(cin, abc);
    getline(cin, abc);
    vector<string> banned(p);
    Node root;
    root.id = node_num++;
    for (int i = 0; i < p; ++i) {
        Node* cur_node = &root;
        cin >> banned[i];
        for (auto symb : banned[i]) {
            auto it = cur_node->transition.find(symb);
            if (it == cur_node->transition.end()) {
                auto node = make_shared<Node>();
                node->parent = cur_node;
                node->p_symb = symb;
                node->id = node_num++;
                cur_node->transition[symb] = node;
                cur_node = node.get();
            } else {
                cur_node = it->second.get();
            }
        }
        cur_node->terminal = true;
        cur_node->transition.clear();
        terminal.insert(cur_node->id);
    }
    root.link = &root;
    queue<Node*> q;
    q.push(&root);
    while(!q.empty()) {
        auto cur_node = q.front();
        q.pop();
        if (cur_node->terminal) {
            continue;
        }
        if (!cur_node->link) {
            auto p = cur_node->parent;
            auto c = cur_node->p_symb;
            auto link = p->link;
            do {
                auto it = link->transition.find(c);
                if (it == link->transition.end() || it->second.get() == cur_node) {
                    if (link == link->link) {
                        break;
                    }
                    link = link->link;
                } else {
                    cur_node->link = it->second.get();
                    if (cur_node->link->terminal) {
                        cur_node->terminal = true;
                        terminal.insert(cur_node->id);
                        cur_node->transition.clear();
                    }
                    break;
                }
            } while(true);
            if (!cur_node->link) {
                cur_node->link = &root;
            }
        }
        for (auto next : cur_node->transition)
            q.push(next.second.get());
    }
    q.push(&root);
    vector<vector<int>> adj(node_num, vector<int>(node_num, 0));
    while(!q.empty()) {
        auto cur_node = q.front();
        q.pop();
        if (cur_node->terminal) {
            continue;
        }
        for (auto c : abc) {
            auto* node = cur_node;
            do {
                auto it = node->transition.find(c);
                if (it != node->transition.end()) {
                    adj[cur_node->id][it->second->id] += 1;
                    break;
                }
                if (node == node->link) {
                    adj[cur_node->id][0] += 1;
                    break;
                }
                node = node->link;
            } while (true);
        }
        for (auto next : cur_node->transition)
            q.push(next.second.get());
    }
    vector<vector<BigInteger>> res_matrix(node_num, vector<BigInteger>(node_num, BigInteger(0)));
    for (int i = 0; i < node_num; ++i)
    {
        res_matrix[i][i] = BigInteger(1);
    }
    vv_big pw = mult(res_matrix, adj);
    while (m > 0)
    {
        if (m % 2) {
            res_matrix = mult(res_matrix, pw);
        }
        m /= 2;
        pw = mult(pw, pw);
    }
    BigInteger res(0);
    for (int i = 0; i < node_num; ++i)
        if (terminal.find(i) == terminal.end())
            res += res_matrix[0][i];
    cout << res.toString() << endl;
    return 0;
}
