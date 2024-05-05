#include <curl/curl.h>
#include "json.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

size_t write_function(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

using CurlPtr = std::unique_ptr<CURL, std::function<void(CURL*)>>;

CurlPtr create_curl()
{
    return CurlPtr(curl_easy_init(), [](CURL* curl) {
                                        if (curl)
                                        {
                                            curl_easy_cleanup(curl);
                                        }
                                      });
}

struct Node
{
    std::string name;
    Node* parent;
    std::vector<std::unique_ptr<Node>> children;
    size_t sz;
};

std::string make_full_path(Node* node)
{
    std::string path;
    while (node->parent)
    {
        path = "/" + node->name + path;
        node = node->parent;
    }
    return path.empty() ? "/" : path;
}

void dfs(Node* node, std::string& prefix)
{
    std::cout << "/" << prefix << node->name << std::endl;
    for (auto& c : node->children)
    {
        if (node->name.empty())
        {
            dfs(c.get(), prefix);
        }
        else
        {
            size_t old_size = prefix.size();
            prefix += node->name + "/";
            dfs(c.get(), prefix);
            prefix.resize(old_size);
        }
    }
}

int main()
{
    int batch_size = 0;
    {
        auto curl = create_curl();
        if (!curl)
        {
            return -1;
        }
        std::string username;
        std::getline(std::cin, username);

        char buf[1024];
        std::sprintf(buf, "127.0.0.1:7777/start/session?login=%s", username.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_URL, buf);

        std::string response_string;
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_function);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response_string);

        curl_easy_perform(curl.get());
        auto resp_json = nlohmann::json::parse(response_string);
        batch_size = resp_json["max_batch_size"].get<int>();
    }

    Node root;
    root.parent = nullptr;
    root.name = "";
    auto node_cmp = [](Node* lhs, Node* rhs) {return lhs->sz > rhs->sz;};
    std::vector<Node*> q;
    root.sz = 0;
    q.push_back(&root);
    size_t cnt = 1;
    while (!q.empty())
    {
        std::vector<Node*> active_nodes;
        std::vector<std::string> batch;
        size_t cur_batch_size = 0;
        std::vector<Node*> next_q;
        for (auto node : q)
        {
            if (cur_batch_size + node->sz <= batch_size)
            {
                active_nodes.push_back(node);
                auto path = make_full_path(node);
                batch.emplace_back(std::move(path));
                cur_batch_size += node->sz;
            }
            else
            {
                next_q.push_back(node);
            }
        }
        std::swap(q, next_q);
        nlohmann::json payload_json;
        payload_json["paths"] = batch;
        std::string payload = payload_json.dump(0);
        // std::cout << "request = " << payload << std::endl;

        auto curl = create_curl();
        curl_easy_setopt(curl.get(), CURLOPT_URL, "127.0.0.1:7777/ls/batch");
        curl_easy_setopt(curl.get(), CURLOPT_POST, 1L);
        curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, payload.c_str());
        std::string response_string;
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_function);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response_string);
        curl_easy_perform(curl.get());

        // std::cout << "response = " << response_string << std::endl;
        auto response_json = nlohmann::json::parse(response_string);
        const auto& fs_list = response_json["listings"];
        for (size_t i = 0; i < fs_list.size(); ++i)
        {
            for (const auto& elem : fs_list[i])
            {
                auto next_node = std::unique_ptr<Node>(new Node());
                next_node->name = elem["name"];
                if (next_node->name.back() == '/')
                {
                    next_node->name.pop_back();
                }
                next_node->parent = active_nodes[i];
                next_node->sz = elem["size"].get<int>();
                if (next_node->sz > 0)
                {
                    q.push_back(next_node.get());
                }
                active_nodes[i]->children.emplace_back(std::move(next_node));
                ++cnt;
            }
        }
        std::sort(q.begin(), q.end(), node_cmp);
    }
    std::cout << cnt << std::endl;
    std::vector<Node*> st;
    st.push_back(&root);
    while (!st.empty())
    {
        auto node = st.back();
        std::sort(node->children.begin(), node->children.end(),
                  [](const std::unique_ptr<Node>& lhs, const std::unique_ptr<Node>& rhs)
                  {
                    return std::lexicographical_compare(lhs->name.begin(), lhs->name.end(), rhs->name.begin(), rhs->name.end());
                  });
        st.pop_back();
    }

    std::string prefix;
    dfs(&root, prefix);

    return 0;
}
