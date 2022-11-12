#include <iostream>
#include "json.hpp"
#include <queue>
#include <regex>

using namespace std;

enum ValType
{
    INT,
    STR,
    NONE
};

struct Node
{
    string str_val;
    size_t val{0};
    ValType t;
    std::map<string, size_t> children;
    int parent{-1};
    string label;
    std::vector<size_t> good_leaf;
};

std::vector<string> tokenize(std::string str)
{
    if (str[0] == '.')
    {
        str.erase(0, 1);
    }
    if (str.back() == '.')
        str.pop_back();
    vector<string> path;
    if (!str.empty())
    {
        size_t pos = 0;
        while (true)
        {
            if (pos == str.size())
            {
                break;
            }
            size_t next_pos = str.find('.', pos);
            if (next_pos == string::npos)
            {
                path.push_back(str.substr(pos, str.size() - pos));
                break;
            }
            path.push_back(str.substr(pos, next_pos - pos));
            pos = next_pos + 1;
        }
    }
    return path;
}

int main()
{
    string line;
    getline(cin, line);
    auto json = nlohmann::json::parse(line);
    int t;
    cin >> t;
    std::vector<Node> nodes;
    std::queue<std::pair<size_t, nlohmann::json*>> q;
    nodes.push_back(Node{});
    q.push(make_pair(static_cast<size_t>(0), &json));

    while (!q.empty())
    {
        size_t idx = q.front().first;
        nlohmann::json* cur_json = q.front().second;
        q.pop();
        for (auto it = cur_json->begin(); it != cur_json->end(); ++it)
        {
            auto& ch = it.value();
            size_t child_idx = nodes.size();
            nodes.push_back(Node{});
            nodes[idx].children[it.key()] = child_idx;
            nodes.back().parent = idx;
            nodes.back().label = it.key();
            if (ch.is_object())
            {
                q.push(make_pair(child_idx, &ch));
            }
            else
            {
                if (ch.is_null())
                {
                    nodes.back().t = ValType::NONE;
                }
                else if (ch.is_string())
                {
                    nodes.back().t = ValType::STR;
                    nodes.back().str_val = ch.get<string>();
                }
                else
                {
                    nodes.back().t = ValType::INT;
                    nodes.back().val = ch.get<int>();
                }
            }
        }
    }

    getline(cin, line);
    for (int o = 0; o < t; ++o)
    {
        for (auto& x: nodes)
            x.good_leaf.clear();
        getline(cin, line);
        auto req_json = nlohmann::json::parse(line);
        string req = req_json["path"].get<string>();
        string regex_req;
        for (auto c : req)
        {
            if (c == '.')
                regex_req += '\\';
            if (c == '*')
                regex_req += '.';
            regex_req += c;
        }
        regex r(regex_req);
        int cnt = req_json["count"].get<int>();
        size_t a_pos = req.find('*');
        string prefix = req.substr(0, a_pos);
        string suffix = req.substr(a_pos + 1, req.size() - a_pos);
        auto suffix_path = tokenize(suffix);
        auto prefix_path = tokenize(prefix);
        reverse(suffix_path.begin(), suffix_path.end());
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            if (nodes[i].children.empty())
            {
                //cout << "child label = " << nodes[i].label << endl;
                size_t cur_idx = i;
                bool found = true;
                for (auto& x : suffix_path)
                {
                    //cout << "Matching suffix = " << x << endl;
                    if (cur_idx == 0 || nodes[cur_idx].label != x)
                    {
                        //cout << "Fail" << endl;
                        found = false;
                        break;
                    }
                    cur_idx = nodes[cur_idx].parent;
                }
                if (found)
                {
                    //cout << "Append " << last_idx << " to " << i << endl;
                    nodes[cur_idx].good_leaf.push_back(i);
                }
            }
        }
        bool found = true;
        size_t cur_idx = 0;
        for (auto& x : prefix_path)
        {
            auto& cur_node = nodes[cur_idx];
            auto it = cur_node.children.find(x);
            if (it == cur_node.children.end())
            {
                found = false;
                break;
            }
            cur_idx = it->second;
        }
        if (!found)
        {
            nlohmann::json res;
            res["result"] = std::vector<int>{};
            cout << res.dump() << endl;
            continue;
        }
        //cout << "cur_idx = " << cur_idx << endl;
        queue<size_t> q;
        vector<string> str_val;
        vector<size_t> int_val;
        for (auto& x : nodes[cur_idx].children)
        {
            q.push(x.second);
        }
        while (!q.empty())
        {
            size_t i = q.front();
            q.pop();
            if (!nodes[i].good_leaf.empty())
            {
                for (auto x : nodes[i].good_leaf)
                {
                    switch (nodes[x].t)
                    {
                    case ValType::NONE:
                        break;
                    case ValType::INT:
                        int_val.push_back(nodes[x].val);
                        break;
                    case ValType::STR:
                        str_val.push_back(nodes[x].str_val);
                        break;
                    }
                }
            }
            for (auto& x : nodes[i].children)
            {
                q.push(x.second);
            }
        }
        if (int_val.size() > 0 && str_val.size() > 0)
        {
            cout << "{\"result\":null}" << endl;
            continue;
        }
        if (int_val.size() == 0 && str_val.size() == 0)
        {
            cout << "{\"result\":[]}" << endl;
            continue;
        }
        if (int_val.size() > 0)
        {
            sort(int_val.rbegin(), int_val.rend());
            if (cnt < int_val.size())
            {
                int_val.resize(cnt);
            }
            nlohmann::json res;
            res["result"] = int_val;
            cout << res.dump() << endl;
            continue;
        }
        if (str_val.size() > 0)
        {
            sort(str_val.rbegin(), str_val.rend());
            if (cnt < str_val.size())
            {
                str_val.resize(cnt);
            }
            nlohmann::json res;
            res["result"] = str_val;
            cout << res.dump() << endl;
            continue;
        }
    }
    return 0;
}
