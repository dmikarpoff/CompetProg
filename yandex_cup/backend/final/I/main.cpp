#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

struct BlockRef {
    uint64_t offset;
    uint64_t len;
};

bool operator<(const BlockRef& lhs, const BlockRef& rhs) {
    return lhs.offset < rhs.offset;
}

struct Block {
    bool ref;
    union {
        BlockRef block_ref;
        char symb;
    } data;
};

struct Extractor {
    uint64_t offset;
    uint64_t len;
    uint64_t pos;
};

std::map<BlockRef, std::string> cache;

std::string decompress_without_cache(uint64_t offset, uint64_t len, const std::vector<Block>& block,
                                     const std::vector<uint64_t>& pos);

std::string decompress(uint64_t offset, uint64_t len, const std::vector<Block>& block,
                       const std::vector<uint64_t>& pos) {
    auto b = cache.lower_bound({offset, 0});
    if (b != cache.begin()) {
        auto j = b;
        --j;
        if (j->first.offset + j->first.len > offset) {
            b = j;
        }
    }
    auto e = cache.lower_bound({offset + len, 0});

    uint64_t first_char = offset;
    std::string res(len, 1);
    uint64_t rem_len = len;
    bool update_cache = false;
//    std::cout << "Decompressing " << offset << " " << len << std::endl;
    std::vector<Extractor> to_extract;
    for (auto i = b; i != e;) {
        if (i->first.offset <= first_char) {
            uint64_t cache_len = std::min(i->first.len + i->first.offset - first_char, rem_len);
            uint64_t dest_offset = first_char - offset;
            uint64_t src_offset = first_char - i->first.offset;
            std::copy(i->second.begin() + src_offset, i->second.begin() + src_offset + cache_len,
                      res.begin() + dest_offset);
//            std::cout << "Cache hit = " << res << std::endl;
            first_char += cache_len;
            rem_len -= cache_len;
            ++i;
        } else {
            update_cache = true;
            to_extract.push_back(Extractor{first_char, i->first.offset - first_char, first_char - offset});
//            std::cout << "Extracting = " << res << std::endl;
            rem_len -= i->first.offset - first_char;
            first_char = i->first.offset;
        }
    }
    if (first_char < offset + len) {
        update_cache = true;
        to_extract.push_back(Extractor{first_char, offset + len - first_char, first_char - offset});
    }
    for (auto extr : to_extract) {
        auto t = decompress_without_cache(extr.offset, extr.len, block, pos);
        std::copy(t.begin(), t.end(), res.begin() + extr.pos);
    }
    assert(res.size() == len);
//------------------------------------------------

    if (update_cache && res.size() > 1) {
        auto b = cache.lower_bound({offset, 0});
        if (b != cache.begin()) {
            auto j = b;
            --j;
            if (j->first.offset + j->first.len > offset) {
                b = j;
            }
        }
        auto e = cache.lower_bound({offset + len, 0});
        cache.erase(b, e);
        cache[{offset, len}] = res;
    }

    return res;
}

std::string decompress_without_cache(uint64_t offset, uint64_t len, const std::vector<Block>& block,
                                     const std::vector<uint64_t>& pos) {
    std::string res;
    auto begin_idx = std::upper_bound(pos.begin(), pos.end(), offset) - pos.begin();
    --begin_idx;
    auto end_idx = std::lower_bound(pos.begin(), pos.end(), offset + len) - pos.begin();

    size_t rem_len = len;
    for (int i = begin_idx; i < end_idx; ++i) {
        if (block[i].ref) {
            uint64_t next_offset = block[i].data.block_ref.offset;
            uint64_t next_len = block[i].data.block_ref.len;
            if (offset > pos[i]) {
                next_offset += offset - pos[i];
                next_len = next_len + pos[i] - offset;
            }
            next_len = std::min<size_t>(rem_len, next_len);
            res += decompress(next_offset, next_len, block, pos);
            rem_len -= next_len;
        } else {
            res += block[i].data.symb;
            rem_len -= 1;
        }
    }
    return res;
}

int main()
{
    std::string req;
    std::getline(std::cin, req);
    std::vector<int> p(req.size(), -1);
    for (int i = 1; i < p.size(); ++i) {
        int u = p[i - 1];
        for (;;) {
            if (req[i] == req[u + 1]) {
                p[i] = u + 1;
                break;
            }
            if (u == -1) {
                break;
            }
            u = p[u];
        }
    }
    std::string line;
    std::getline(std::cin, line);
    int n = std::stoi(line);
    char splitter = '\t';
    std::vector<Block> blocks;
    std::vector<uint64_t> block_pos;
    blocks.reserve(n);
    block_pos.reserve(n);
    uint64_t block_offset = 0;
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        uint64_t pos = line.find(splitter);
        int code = std::stoi(line.substr(0, pos));
        block_pos.push_back(block_offset);
        if (code == 0) {
            char letter = line[pos + 1];
            blocks.emplace_back();
            blocks.back().ref = false;
            blocks.back().data.symb = letter;
            ++block_offset;
        } else if (code == 1) {
            std::stringstream ss(line);
            int unused;
            uint64_t from, len;
            ss >> unused >> from >> len;
            blocks.emplace_back();
            blocks.back().ref = true;
            blocks.back().data.block_ref = BlockRef{from, len};
            block_offset += len;
        } else {
            return -1;
        }
    }
    block_pos.push_back(block_offset);
    if (req.size() == 1) {
        for (uint64_t i = 0; i < blocks.size(); ++i) {
            if (!blocks[i].ref && blocks[i].data.symb == req[0]) {
                std::cout << "YES" << std::endl;
                std::cout << block_pos[i] << std::endl;
                return 0;
            }
        }
        std::cout << "NO" << std::endl;
        return 0;
    }
    for (uint64_t i = 0; i + 1 < blocks.size(); ++i) {
//        std::cout << "Block " << i << "-------------------" << std::endl;
        std::string decompressed;
        uint64_t decomp_position = block_pos[i + 1];
        decompressed.reserve(2 * (req.size() - 1));
        if (blocks[i].ref) {
            uint64_t offset = blocks[i].data.block_ref.offset;
            uint64_t len = blocks[i].data.block_ref.len;
            if (len > req.size() - 1) {
                offset += len - req.size() + 1;
                len = req.size() - 1;
            }
            decomp_position -= len;
            decompressed = decompress(offset, len, blocks, block_pos);
            // cache[{decomp_position, len}] = decompressed;
        } else {
            decompressed += blocks[i].data.symb;
            decomp_position -= 1;
            // cache[{decomp_position, 1}] = std::string{blocks[i].data.symb, 1};
        }
        for (uint64_t j = i + 1, suffix_len = 0; j < blocks.size(); ++j) {
            if (blocks[j].ref) {
                uint64_t rem = req.size() - 1 - suffix_len;
                uint64_t offset = blocks[j].data.block_ref.offset;
                uint64_t len = blocks[j].data.block_ref.len;
                len = std::min(rem, len);
                suffix_len += len;
                decompressed += decompress(offset, len, blocks, block_pos);
            } else {
                decompressed += blocks[j].data.symb;
                ++suffix_len;
            }
            if (suffix_len + 1 == req.size()) {
                break;
            }
        }
        if (decompressed.size() < req.size()) {
            continue;
        }
        int matched = -1;
        for (size_t j = 0; j < decompressed.size(); ++j) {
            for (;;) {
                if (decompressed[j] == req[matched + 1]) {
                    ++matched;
                    break;
                }
                if (matched == -1) {
                    break;
                }
                matched = p[matched];
            }
            if (matched + 1 == req.size()) {
                std::cout << "YES" << std::endl;
                std::cout << decomp_position + j + 1 - req.size() << std::endl;
                return 0;
            }
        }
    }
    std::cout << "NO" << std::endl;
    return 0;
}

/*

abc
4
0 a
1 0 1
0 b
0 c

eac
12
0 a
0 b
0 c
1 0 3
1 0 6
1 0 12
1 8 12
0 x
1 0 34
1 0 68
0 e
1 1 100

ebc
12
0 a
0 b
0 c
1 0 3
1 0 6
1 0 12
1 8 12
0 x
1 0 34
1 0 68
0 e
1 1 100

*/
