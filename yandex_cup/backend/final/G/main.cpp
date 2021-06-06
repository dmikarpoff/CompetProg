#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

using namespace std;

unsigned char data[1000 * 1001];
int16_t valid_string[1000 * 1001];

int main()
{
    std::ifstream in("index.bin", std::ios_base::binary | std::ios_base::in);
    auto after_last = std::copy(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(),
                                std::begin(data));
    size_t data_size = after_last - std::begin(data);
    std::vector<std::pair<uint32_t, uint32_t>> descr;
    descr.reserve(1001 * 1000);
    for (size_t i = 0; i < data_size; ++i) {
        uint8_t sz = data[i];
        if (sz < 9 || sz > 127) {
            for (const auto& p: descr) {
                if (p.first + p.second < i) {
                    valid_string[p.first] = p.second;
                } else {
                    valid_string[p.first] = -1;
                }
            }
            descr.clear();
        }
        descr.emplace_back(i, sz);
    }
    for (auto p: descr) {
        if (p.first + p.second < data_size) {
            valid_string[p.first] = p.second;
        } else {
            valid_string[p.first] = -1;
        }
    }
    /*
    for (size_t i = 0; i < data_size; ++i)
        std::cout << valid_string[i] << " ";
    std::cout << std::endl;
    */
    std::vector<std::pair<uint64_t, uint64_t>> res;
    std::vector<int> sum;
    sum.resize(1000 * 1001);
    for (size_t o = 0; o < 4; ++o) {
        descr.clear();
        sum.clear();
        int cur_sum = 0;
        for (uint64_t i = o; i + 3 < data_size; i += 4)
        {
            uint32_t list_len = *reinterpret_cast<uint32_t*>(data + i);
            if (list_len >= data_size || valid_string[list_len] == -1) {
                for (size_t j = 0; j < descr.size(); ++j) {
                    if (descr[j].first + 4 * (descr[j].second + 1) <= i) {
                        res.emplace_back(descr[j].first, sum[descr[j].first + 4 * descr[j].second] - sum[descr[j].first]);
                    }
                }
                descr.clear();
                sum.clear();
                cur_sum = 0;
            } else {
                cur_sum += valid_string[list_len];
            }
            if (list_len != 0 && list_len <= data_size) {
                descr.emplace_back(i, list_len);
            }
            sum[i] = cur_sum;
        }
        for (size_t j = 0; j < descr.size(); ++j) {
            if (descr[j].first + 4 * (descr[j].second + 1) <= data_size) {
                res.emplace_back(descr[j].first, sum[descr[j].first + 4 * descr[j].second] - sum[descr[j].first]);
            }
        }
    }
    std::sort(res.begin(), res.end());
    std::cout << res.size() << std::endl;
    for (auto p : res) {
        std::cout << p.first << " " << p.second << std::endl;
    }
    return 0;
}
