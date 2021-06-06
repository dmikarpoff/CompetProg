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
#include <set>

#include <cmath>
#include <algorithm>
#include <numeric>
#include <cstdint>

#include "json.hpp"

struct Book {
    std::string id;
    std::vector<std::shared_ptr<Book>> children;
};

enum class CompareRes {
    kLess,
    kGreater,
    kEqual
};

CompareRes spaceship(const Book& lhs, const Book& rhs) {
    if (lhs.children.size() < rhs.children.size()) {
        return CompareRes::kLess;
    }
    if (lhs.children.size() > rhs.children.size()) {
        return CompareRes::kGreater;
    }
    for (size_t i = 0; i < lhs.children.size(); ++i) {
        auto res = spaceship(*lhs.children[i], *rhs.children[i]);
        if (res != CompareRes::kEqual) {
            return res;
        }
    }
    return CompareRes::kEqual;
}

bool operator<(const Book& lhs, const Book& rhs) {
    return spaceship(lhs, rhs) == CompareRes::kLess;
}

template <class T, class F>
void fill_book(Book* book, const T& json, std::vector<size_t>& cur_path,
               std::map<std::string, std::vector<size_t>>& problems_map,
               F& f) {
    if (json.find("sections") != json.end()) {
        for (const auto& section: json["sections"]) {
            book->children.emplace_back(std::make_shared<Book>());
            cur_path.push_back(book->children.size() - 1);
            fill_book(book->children.back().get(), section, cur_path, problems_map, f);
            cur_path.pop_back();
        }
    }
    if (json.find("problems") != json.end()) {
        for (const auto& problem: json["problems"]) {
            book->children.emplace_back(std::make_shared<Book>());
            std::vector<size_t> path = cur_path;
            path.push_back(book->children.size() - 1);
            book->children.back()->id = problem["id"];
            problems_map[problem["id"]] = std::move(path);
            f(problem["id"]);
        }
    }
}

int main()
{
    std::string request;
    std::map<Book, std::vector<std::pair<std::string, size_t>>> books;
    std::map<std::string, std::map<std::string, std::vector<size_t>>> path_to_problem;
    std::map<std::string, std::map<std::string, size_t>> problem_to_book;
    std::vector<Book> book_vector;
    while (std::getline(std::cin, request)) {
        if (request == "add") {
            std::string site_name, json_descr;
            std::getline(std::cin, site_name);
            std::getline(std::cin, json_descr);
            auto parsed_descr = nlohmann::json::parse(json_descr);
            Book book;
            auto& problems_map = path_to_problem[site_name];
            std::vector<size_t> temp;
            auto& p_to_book = problem_to_book[site_name];
            size_t idx = book_vector.size();
            auto problem_callback = [&p_to_book, idx](const std::string& id) {
                p_to_book[id] = idx;
            };
            fill_book(&book, parsed_descr, temp, problems_map, problem_callback);
            books[book].push_back(std::make_pair(site_name, book_vector.size()));
            book_vector.push_back(book);
        } else if (request == "find") {
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            std::string site, id;
            ss >> site >> id;
            size_t book_idx = problem_to_book[site][id];
            const auto& found_books = books[book_vector[book_idx]];
            std::cout << found_books.size() - 1 << std::endl;
            const std::vector<size_t>& path = path_to_problem[site][id];
            for (const auto& p: found_books) {
                if (p.first == site) {
                    continue;
                }
                const Book* b = &(book_vector[p.second]);
                for (auto u: path) {
                    b = b->children[u].get();
                }
                std::cout << p.first << " " << b->id << std::endl;
            }
        } else {
            break;
        }
    }
    return 0;
}
