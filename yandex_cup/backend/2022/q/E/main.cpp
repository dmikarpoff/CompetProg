#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Node
{
    map<char, size_t> next;
    map<string, int> ext;
    bool last = false;
};

int main()
{
    int n;
    cin >> n;
    vector<Node> prefix;
    prefix.reserve(600000);
    prefix.push_back(Node{});
    for (int i = 0; i < n; ++i)
    {
        string dir;
        cin >> dir;
        Node* cur_node = &prefix[0];
        for (char c : dir)
        {
            if (cur_node->last)
            {
                break;
            }
            auto it = cur_node->next.find(c);
            if (it == cur_node->next.end())
            {
                cur_node->next[c] = prefix.size();
                prefix.push_back(Node());
                cur_node = &prefix.back();
            }
            else
            {
                cur_node = &prefix[it->second];
            }
        }
        cur_node->last = true;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        string f;
        cin >> f;
        size_t ext_pos = f.find('.');
        string ext = string(f.begin() + ext_pos + 1, f.end());
        Node* cur_node = &prefix[0];
        bool has_prefix = false;
        for (char c : f)
        {
            // cout << c << endl;
            if (cur_node->last)
            {
                has_prefix = true;
                break;
            }
            auto it = cur_node->next.find(c);
            if (it == cur_node->next.end())
            {
                break;
            }
            cur_node = &prefix[it->second];
        }
        if (!has_prefix)
        {
            continue;
        }
        cur_node = &prefix[0];
        for (char c : f)
        {
            if (c == '/')
            {
                cur_node->ext[ext]++;
            }
            auto it = cur_node->next.find(c);
            if (it == cur_node->next.end())
            {
                cur_node->next[c] = prefix.size();
                prefix.push_back(Node());
                cur_node = &prefix.back();
            }
            else
            {
                cur_node = &prefix[it->second];
            }
        }
    }
    /*
    cout << prefix[0].ext.size() << endl;
    for (const auto &p: prefix[0].ext)
    {
        cout << p.first << ": " << p.second << endl;
    }
    */
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        string dir;
        cin >> dir;
        dir.pop_back();
        Node* cur_node = &prefix[0];
        bool found = true;
        for (char c : dir)
        {
            auto it = cur_node->next.find(c);
            if (it == cur_node->next.end())
            {
                found = false;
                break;
            }
            cur_node = &prefix[it->second];
        }
        if (found)
        {
            cout << cur_node->ext.size() << endl;
            for (const auto& p : cur_node->ext)
            {
                cout << '.' << p.first << ": " << p.second << endl;
            }
        }
        else
        {
            cout << 0 << endl;
        }
    }
    return 0;
}
