#include <iostream>
#include <vector>
#include <memory>

using namespace std;

enum class CellState
{
  Undef,
  Empty,
  Cross,
  Oath
};

struct Desk
{
  CellState val[3][3];
  bool check(int* res)
  {
    for (int i = 0; i < 3; ++i)
    {
      int crosses = 0;
      int oaths = 0;
      for (int j = 0; j < 3; ++j)
      {
        if (val[i][j] == CellState::Cross)
          crosses++;
        if (val[i][j] == CellState::Oath)
          oaths++;
      }
      if (crosses == 3)
      {
        *res = 1;
        return true;
      }
      if (oaths == 3)
      {
        *res = -1;
        return true;
      }
      crosses = 0;
      oaths = 0;
      for (int j = 0; j < 3; ++j)
      {
        if (val[j][i] == CellState::Cross)
          crosses++;
        if (val[j][i] == CellState::Oath)
          oaths++;
      }
      if (crosses == 3)
      {
        *res = 1;
        return true;
      }
      if (oaths == 3)
      {
        *res = -1;
        return true;
      }
    }
    {
      int crosses = 0;
      int oaths = 0;
      for (int i = 0; i < 3; ++i)
      {
        if (val[i][i] == CellState::Cross)
          ++crosses;
        if (val[i][i] == CellState::Oath)
          ++oaths;
      }
      if (crosses == 3)
      {
        *res = 1;
        return true;
      }
      if (oaths == 3)
      {
        *res = -1;
        return true;
      }
    }
    {
      int crosses = 0;
      int oaths = 0;
      for (int i = 0; i < 3; ++i)
      {
        if (val[2 - i][i] == CellState::Cross)
          ++crosses;
        if (val[2 - i][i] == CellState::Oath)
          ++oaths;
      }
      if (crosses == 3)
      {
        *res = 1;
        return true;
      }
      if (oaths == 3)
      {
        *res = -1;
        return true;
      }
    }
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        if (val[i][j] == CellState::Empty)
          return false;
    *res = 0;
    return true;
  }
};

struct Node
{
  Desk desk;
  std::vector<std::unique_ptr<Node>> children;
  int mark;
};

void dfs(Node* node, bool cross)
{
//  cout << "Entering node" << endl;
  int res;
  if (node->desk.check(&res))
  {
//    cout << "Result ready" << endl;
    node->mark = res;
    return;
  }
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      if (node->desk.val[i][j] == CellState::Empty)
      {
//        cout << "Add mark " << i << " " << j << endl;
        node->children.emplace_back(new Node());
        Node* ch = node->children.back().get();
        ch->desk = node->desk;
        ch->desk.val[i][j] = cross ? CellState::Cross : CellState::Oath;
        dfs(ch, !cross);
      }
    bool win = false, draw = false;
    for (auto& ch : node->children)
    {
      if (ch->mark == 0)
      {
        draw = true;
        continue;
      }
      if (ch->mark == (cross ? 1 : -1))
        win = true;
    }
    if (win)
    {
      node->mark = (cross ? 1 : -1);
    }
    else if (draw)
    {
      node->mark = 0;
    }
    else
    {
      node->mark = (cross ? -1 : 1);
    }
//    cout << "Mark = " << node->mark << endl;
}

int main()
{
  Node root;
  for (int i = 0; i < 3; ++i)
  {
    string s;
    cin >> s;
    for (int j = 0; j < 3; ++j)
    {
      switch (s[j])
      {
      case 'X':
        root.desk.val[i][j] = CellState::Cross;
        break;
      case 'O':
        root.desk.val[i][j] = CellState::Oath;
        break;
      case '#':
        root.desk.val[i][j] = CellState::Empty;
        break;
      default:
        return -1;
      }
    }
  }
  dfs(&root, true);
  if (root.mark == 1)
    cout << "Crosses win" << endl;
  else if (root.mark == 0)
    cout << "Draw" << endl;
  else
    cout << "Ouths win" << endl;
  return 0;
}
