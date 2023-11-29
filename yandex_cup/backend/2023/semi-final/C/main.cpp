#include <iostream>
#include <sstream>
#include <unordered_map>
#include <memory>

using namespace std;

struct Node
{
    Node* parent = nullptr;
    unordered_map<string, bool> read;
    unordered_map<string, bool> write;
    unordered_map<string, unique_ptr<Node>> children;
};

int main()
{
    string cmd;
    Node root;
    while (getline(cin, cmd))
    {
        stringstream ss(cmd);
        string type, user, mode, path;
        ss >> type >> user >> mode >> path;
        if (type == "grant" || type == "block")
        {
            Node* cur_node = &root;
            if (path.size() > 1)
            {
                size_t pos = 1;
                size_t next_pos = path.find('/', pos);
                while (next_pos != string::npos)
                {
                    string name = string(path.begin() + pos, path.begin() + next_pos);
                    auto& cur_node_ptr = cur_node->children[name];
                    if (!cur_node_ptr)
                    {
                        cur_node_ptr.reset(new Node());
                        cur_node_ptr->parent = cur_node;
                    }
                    cur_node = cur_node_ptr.get();
                    pos = next_pos + 1;
                    next_pos = path.find('/', pos);
                    //cout << name << endl;
                }
                string name{path.begin() + pos, path.end()};
                auto& cur_node_ptr = cur_node->children[name];
                if (!cur_node_ptr)
                {
                    cur_node_ptr.reset(new Node());
                    cur_node_ptr->parent = cur_node;
                }
                cur_node = cur_node_ptr.get();
            }
            if (mode == "read")
            {
                cur_node->read[user] = (type == "grant");
            }
            else if (mode == "write")
            {
                cur_node->write[user] = (type == "grant");
            }
            cout << "done" << endl;
            continue;
        }
        if (type == "check")
        {
            Node* cur_node = &root;
            if (path.size() > 1)
            {
                size_t pos = 1;
                size_t next_pos = path.find('/', pos);
                bool not_found = false;
                while (next_pos != string::npos)
                {
                    string name = string(path.begin() + pos, path.begin() + next_pos);
                    auto it = cur_node->children.find(name);
                    if (it == cur_node->children.end())
                    {
                        not_found = true;
                        break;
                    }
                    cur_node = it->second.get();
                    pos = next_pos + 1;
                    next_pos = path.find('/', pos);
                }
                if (!not_found)
                {
                    string name{path.begin() + pos, path.end()};
                    auto it = cur_node->children.find(name);
                    if (it != cur_node->children.end())
                    {
                        cur_node = it->second.get();
                    }
                    else
                    {
                        not_found = true;
                    }
                }
            }
            do
            {
                if (mode == "read")
                {
                    auto it = cur_node->read.find(user);
                    if (it == cur_node->read.end())
                    {
                        cur_node = cur_node->parent;
                    }
                    else
                    {
                        cout << (it->second ? "allowed" : "forbidden") << endl;
                        break;
                    }
                }
                else if (mode == "write")
                {
                    auto it = cur_node->write.find(user);
                    if (it == cur_node->write.end())
                    {
                        cur_node = cur_node->parent;
                    }
                    else
                    {
                        cout << (it->second ? "allowed" : "forbidden") << endl;
                        break;
                    }
                }
            }
            while (cur_node != nullptr);
            if (cur_node == nullptr)
            {
                cout << "forbidden" << endl;
            }
            continue;
        }
        return -1;
    }
    return 0;
}
