#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdint>

#include <curl/curl.h>
#include "json.hpp"

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
//    std::cout << size << " " << nmemb << std::endl;
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

int main()
{
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl{curl_easy_init(), &curl_easy_cleanup};
    if (!curl) {
      return 1;
    }
    std::string url;
    std::getline(std::cin, url);
    int port, a, b;
    std::cin >> port >> a >> b;
    url += "?a=" + std::to_string(a) + "&b=" + std::to_string(b);
//    std::cout << url << std::endl;
    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_PORT, port);
    curl_easy_setopt(curl.get(), CURLOPT_CUSTOMREQUEST, "GET");

    std::string response;
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response);

    auto response_code = curl_easy_perform(curl.get());
//    std::cout << response_code << std::endl;
    if (response_code != CURLE_OK) {
        // std::cout << response_code << std::endl;
        return -1;
    }

    auto str_json = nlohmann::json::parse(response);
    std::vector<int64_t> response_vec;
    for (auto x : str_json) {
      response_vec.push_back(x.get<int64_t>());
    }
    std::sort(response_vec.begin(), response_vec.end());
    for (auto x: response_vec) {
        if (x >= 0) {
            break;
        }
        std::cout << x << std::endl;
    }
    return 0;
}
