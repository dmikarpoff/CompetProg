#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int cnt = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    ~Node()
    {
        delete left;
        delete right;
    }
};

int main()
{
    int n;
    cin >> n;
    Node root;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
    {
        int p;
        cin >> p;
//        cout << "For " << p << endl;
        Node* cur_node = &root;
        cur_node->cnt++;
        for (int mask = (1 << 30); mask > 0; mask >>= 1)
        {
            if (p & mask)
            {
//                cout << mask << " right" << endl;
                if (!cur_node->right)
                    cur_node->right = new Node();
                cur_node = cur_node->right;
            }
            else
            {
//                cout << mask << " left" << endl;
                if (!cur_node->left)
                    cur_node->left = new Node();
                cur_node = cur_node->left;
            }
            cur_node->cnt++;
//            cout << "cnt = " << cur_node->cnt <<endl;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        int key = 0;
        Node* cur_node = &root;
        cur_node->cnt--;
//        cout << "For " << a[i] << endl;
        for (int mask = (1 << 30); mask > 0; mask >>= 1)
        {
//            cout << "mask = " << mask << endl;
//            cout << cur_node->cnt + 1 << endl;
            if (cur_node->left && cur_node->right &&
                cur_node->left->cnt && cur_node->right->cnt)
            {
//                cout << "Both possible" << endl;
                if (mask & a[i])
                {
                    cur_node = cur_node->right;
                    key |= mask;
                }
                else
                {
                    cur_node = cur_node->left;
                }
            }
            else
            {
                if (cur_node->left && cur_node->left->cnt)
                {
//                    cout << "taking left" << endl;
                    cur_node = cur_node->left;
                }
                else if (cur_node->right && cur_node->right->cnt)
                {
//                    cout << "taking right" << endl;
                    key |= mask;
                    cur_node = cur_node->right;
                }
            }
            cur_node->cnt--;
//            cout << "key = " << key << endl;
        }
//        cout << key << " " << (key ^ a[i]) << endl;
        cout << (key ^ a[i]) << " ";
    }
    return 0;
}
