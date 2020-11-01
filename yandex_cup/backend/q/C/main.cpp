#include <iostream>
#include <algorithm>

#include "json.hpp"
#include "httplib.h"

int main() {
  httplib::Server serv;
  serv.Get("/ping", [](const httplib::Request& request, httplib::Response& response) {
    response.status = 200;
  });
  serv.Get("/shutdown", [&serv](const httplib::Request& request, httplib::Response& response) {
    serv.stop();
  });
  serv.Get("/validatePassportCode", [](const  httplib::Request& req, httplib::Response& response) {
    if (!req.has_param("passport_code")) {
      response.status = 400;
      return 400;
    }
    response.status = 200;
    std::string passport_id = req.get_param_value("passport_code");
    std::cout << passport_id << std::endl;

    bool has_pc = false;
    if (passport_id.substr(0, 3) == "PC-") {
      passport_id = passport_id.substr(3, passport_id.size() - 3);
      has_pc = true;
    }
    bool valid = true;
    auto minus_pos = passport_id.find('-');
    if (minus_pos == 4) {
      passport_id.erase(passport_id.begin() + 4);
    } else if (has_pc) {
        valid = false;
    }

    auto lparen_pos = passport_id.find('(');
    auto rparen_pos = passport_id.find(')');
    auto space_pos = passport_id.find(' ');
    if (minus_pos != std::string::npos && (lparen_pos != std::string::npos || rparen_pos != std::string::npos || space_pos != std::string::npos)) {
        valid = false;
    }

    if (valid) {
      if (lparen_pos == 0 && rparen_pos == 5) {
        passport_id.erase(rparen_pos, 1);
        passport_id.erase(lparen_pos, 1);
      }
      space_pos = passport_id.find(' ');
      if (space_pos == 4) {
        passport_id.erase(space_pos, 1);
      }
      if (passport_id.size() == 10 && std::all_of(passport_id.begin(), passport_id.end(), [](char c) {return std::isdigit(c);} )) {
        passport_id.insert(4, "-");
        nlohmann::json res;
        res["status"] = true;
        res["normalized"] = passport_id;
        response.set_content(res.dump(), "application/json");
        return 200;
      }
    }

    nlohmann::json res;
    res["status"] = false;
    response.set_content(res.dump(), "application/json");
    return 200;
  });
  serv.Get("/.*", [](const httplib::Request& request, httplib::Response& response) {
      response.status = 404;
  });

  serv.listen("127.0.0.1", 7777);
  return 0;
}
