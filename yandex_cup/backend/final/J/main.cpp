#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "json.hpp"

struct Node {
    std::map<std::string, Node> children;
    std::set<std::string> values;
};

constexpr char kSep = 10;
constexpr char kArr = 9;
size_t max_len = -1;
std::string max_text;

template <class Child, class Key>
void dfs(const nlohmann::json& j, Node& node, const Child& child_callback, const Key& key_callback) {
    if (j.is_array()) {
        for (const auto& e : j) {
            auto* next_node = child_callback(node, std::string() + kArr);
            if (next_node) {
                dfs(e, *next_node, child_callback, key_callback);
            }
        }
        return;
    }
    if (j.is_object()) {
        for (const auto& p : j.items()) {
            auto* next_node = child_callback(node, p.key());
            if (next_node) {
                dfs(p.value(), *next_node, child_callback, key_callback);
            }
        }
        return;
    }
    if (j.is_structured()) {
        std::exit(1);
    }
    try {
        key_callback(node, j.get<std::string>());
    }
    catch (const nlohmann::detail::type_error&) {
    }
}

char buffer[1000 * 1000 * 1000];

int main()
{
    std::string line1, line2;
    std::getline(std::cin, line1);
    std::getline(std::cin, line2);

    nlohmann::json j1 = nlohmann::json::parse(line1);
    Node root;
    dfs(j1, root,
        [](Node& cur_node, const std::string& key) -> Node* {
            auto& next_node = cur_node.children[key];
            return &next_node;
        },
        [](Node& cur_node, const std::string& key) {
            cur_node.values.insert(key);
        });


    nlohmann::json j2 = nlohmann::json::parse(line2);
    dfs(j2, root,
        [](Node& cur_node, const std::string& val) -> Node* {
            auto it = cur_node.children.find(val);
            if (it == cur_node.children.end()) {
                return nullptr;
            }
            return &(it->second);
        },
        [] (Node& cur_node, const std::string& val) {
            if (cur_node.values.find(val) != cur_node.values.end()) {
                if (max_len == static_cast<size_t>(-1) || val.size() > max_len) {
                    max_len = val.size();
                    max_text = val;
                }
            }
        }
    );
    std::cout << (max_len != static_cast<size_t>(-1) ? "YES" : "NO") << std::endl;
    std::cout << max_text << std::endl;
    return 0;
}
