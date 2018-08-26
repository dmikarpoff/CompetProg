#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <memory>

using namespace std;

struct Node
{
  map<char, unique_ptr<Node> > children;
};

bool genWord(const vector<set<char>>& tiles,
             size_t pos, size_t n, Node* root, string* res)
{
  if (pos == n)
  {
//    cout << "Checking " << *res << endl;
    Node* cur_node = root;
    for (size_t i = 0; i < n; ++i)
    {
      auto it = cur_node->children.find((*res)[i]);
      if (it == cur_node->children.end())
        return true;
      cur_node = it->second.get();
    }
    return false;
  }
  for (auto c : tiles[pos])
  {
    *res = *res + c;
    if (genWord(tiles, pos + 1, n, root, res))
      return true;
    res->erase(res->size() - 1, 1);
  }
  return false;
}

int main()
{
    int T;
    cin >> T;
    for (int o = 1; o <= T; ++o)
    {
      int n, l;
      cin >> n >> l;
      vector<set<char>> tile(l);
      Node root;
      for (int i = 0; i < n; ++i)
      {
        string s;
        cin >> s;
        Node* cur_node = &root;
        for (size_t j = 0; j < s.size(); ++j)
        {
          tile[j].insert(s[j]);
          auto it = cur_node->children.find(s[j]);
          if (it == cur_node->children.end())
          {
            cur_node = (cur_node->children[s[j]] = unique_ptr<Node>(new Node)).get();
          }
          else
          {
            cur_node = it->second.get();
          }
        }
      }
      size_t mult = 1;
      size_t idx = -1;
      for (int i = 0; i < l; ++i)
      {
        mult *= tile[i].size();
        if (mult > n)
        {
          idx = i;
          break;
        }
      }
      cout << "Case #" << o << ": ";
      if (idx == -1)
      {
        cout << "-";
      }
      else
      {
        string res;
        genWord(tile, 0, idx + 1, &root, &res);
        for (size_t i = idx + 1; i < l; ++i)
          res += *tile[i].begin();
        cout << res;
      }
      cout << endl;
    }
    return 0;
}
