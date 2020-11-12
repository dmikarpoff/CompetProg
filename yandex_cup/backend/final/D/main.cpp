#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <string>

#include <cmath>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <deque>

struct Command {
    int t;
    std::string key;
    std::string value;
    bool cancelled;
};

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::map<std::string, std::string> storage;
    std::map<int, std::list<Command>> pending;
    std::map<int, std::pair<int, std::list<Command>::iterator>> to_cancel;
    while (line != "-1") {
        std::vector<std::string> tokens;
        size_t i = 0;
        size_t j = line.find("\t");
        while (j != std::string::npos) {
            tokens.push_back(line.substr(i, j - i));
            i = j + 1;
            j = line.find("\t", i);
        }
        tokens.push_back(line.substr(i, line.size() - i));

        int t1 = std::atoi(tokens[0].c_str());
        if (!pending.empty()) {
            auto it = pending.begin();
            while (it != pending.end() && it->first <= t1) {
                for (const auto& cmd : it->second) {
                    if (!cmd.cancelled) {
                        storage[cmd.key] = cmd.value;
                    }
                }
                it = pending.erase(it);
            }
        }

        if (tokens[1] == "set") {
            auto it = storage.find(tokens[3]);
            if (it == storage.end()) {
                std::cout << "false" << std::endl;
            } else {
                std::cout << "true\t" << it->second << std::endl;
            }
            auto t2 = std::atoi(tokens[2].c_str());
            auto pos = pending[t2].insert(pending[t2].end(), Command{t2, std::move(tokens[3]), std::move(tokens[4]), false});
            to_cancel[t1] = make_pair(t2, pos);
        } else if (tokens[1] == "get") {
            auto it = storage.find(tokens[2]);
            if (it == storage.end()) {
                std::cout << "false" << std::endl;
            } else {
                std::cout << "true\t" << it->second << std::endl;
            }
        } else if (tokens[1] == "cancel") {
            auto t = std::atoi(tokens[2].c_str());
            auto i = to_cancel.find(t);
            if (i == to_cancel.end() || i->second.first <= t1 || i->second.second->cancelled) {
                std::cout << "false" << std::endl;
            } else {
                std::cout << "true" << std::endl;
                i->second.second->cancelled = true;
            }
        }


        std::getline(std::cin, line);
    }
    return 0;
}
