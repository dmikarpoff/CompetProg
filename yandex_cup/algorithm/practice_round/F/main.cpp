#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

//#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
#include <iostream>
#endif

struct VecData {
    VecData() = default;
    VecData(int f, int s) : from(f), size(s) {}
    int from = 0;
    int size = 0;
};

struct Pt {
    int x;
    int y;
};

bool operator<(const Pt& lhs, const Pt& rhs) {
    return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}

Pt data[500001];
VecData cell[500001];
int first_black[500001];
int cleared_in_line[500001];
std::pair<int, int> seg_tree[1048576];
int seg_tree_size;
int idx_to_clear[500001];
int idx_to_clear_size;

auto cmp(std::pair<int, int> lhs, std::pair<int, int> rhs) {
    if (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second > rhs.second))
        return lhs;
    return rhs;
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        data[i] = {x, y};
    }

    std::sort(data, data + k);

    int reduced_row_num = 0;
    int last_y = -1;
    for (int i = 0; i < k;) {
        const int cur_y = data[i].y;
//        std::cout << cur_y << " " << last_y << std::endl;
        int sz = 0;
        while (i + sz < k && data[i + sz].y == cur_y) {
            ++sz;
        }
        if (cur_y != last_y + 1) {
            ++reduced_row_num;
        }
        last_y = cur_y;
        cell[reduced_row_num++] = VecData{i, sz};
        i = i + sz;
    }
//    std::cout << "Reduced num = " << reduced_row_num << std::endl;
    m  = reduced_row_num;
    seg_tree_size = 1;
    while (seg_tree_size < m)
        seg_tree_size *= 2;
    for (int i = 0; i < m; ++i) {
        seg_tree[i + seg_tree_size] = std::make_pair(cell[i].size == 0 ? n : data[cell[i].from].x, i);
    }
    for (int i = m; i < seg_tree_size; ++i) {
        seg_tree[i + seg_tree_size] = std::make_pair(n, i);
    }
    for (int i = seg_tree_size - 1; i >= 0; --i) {
        seg_tree[i] = cmp(seg_tree[2 * i], seg_tree[2 * i + 1]);
    }

    int turn = 0;
    int line_to_clear = m - 1;
#ifdef DEBUG_OUTPUT
    std::cout << "--------" << std::endl;
#endif // DEBUG_OUTPUT
    for (;;) {
#ifdef DEBUG_OUTPUT
        std::cout << "Before turn " << turn + 1 << std::endl;
#endif // DEBUG_OUTPUT
        while (line_to_clear >= 0 && cleared_in_line[line_to_clear] == cell[line_to_clear].size) {
            first_black[line_to_clear--] = n;
        }
        if (line_to_clear == -1) {
            break;
        }

        // Even turn
#ifdef DEBUG_OUTPUT
        std::cout << "Even turn ***************" << std::endl;
#endif // DEBUG_OUTPUT
        ++turn;

        idx_to_clear_size = 0;
        for (int bound = 0; bound <= line_to_clear;) {
            auto res = std::make_pair(n, m);
            int l = bound + seg_tree_size;
            int r = line_to_clear + seg_tree_size + 1;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l&1) res = cmp(res, seg_tree[l++]);
                if (r&1) res = cmp(res, seg_tree[--r]);
            }
            int up_bound = res.second;
            int low_bound = up_bound;
            while (low_bound > 0 && seg_tree[seg_tree_size + low_bound - 1].first ==
                                    seg_tree[seg_tree_size + low_bound].first)
                --low_bound;
            for (int b = low_bound; b <= up_bound; ++b) {
                idx_to_clear[idx_to_clear_size++] = b;
            }
#ifdef DEBUG_OUTPUT
            std::cout << bound << " ";
#endif // DEBUG_OUTPUT
            bound = up_bound + 1;
        }
#ifdef DEBUG_OUTPUT
        std::cout << std::endl;
#endif // DEBUG_OUTPUT

        int fb = n;
        for (int idx = idx_to_clear_size - 1; idx >= 0; --idx) {
#ifdef DEBUG_OUTPUT
            std::cout << "Clearing line " << idx_to_clear[idx] << std::endl;
            std::cout << "Black line = " << fb << std::endl;
#endif // DEBUG_OUTPUT
            int& j = cleared_in_line[idx_to_clear[idx]];
            const auto row = data + cell[idx_to_clear[idx]].from;
            if (fb > row[j].x) {
                int front = row[j].x;
                ++j;
                while (j < cell[idx_to_clear[idx]].size &&
                        row[j - 1].x + 1 == row[j].x &&
                        fb > row[j].x) {
                    ++j;
                }
#ifdef DEBUG_OUTPUT
                std::cout << "Cleared " << j << " from " << cell[idx_to_clear[idx]].size << std::endl;
#endif // DEBUG_OUTPUT
                seg_tree[seg_tree_size + idx_to_clear[idx]] =
                    j == cell[idx_to_clear[idx]].size
                        ? std::make_pair(n, idx_to_clear[idx])
                        : std::make_pair(row[j].x, idx_to_clear[idx]);
                for (int h = seg_tree_size + idx_to_clear[idx];
                        h > 1; h /= 2) {
                    seg_tree[h / 2] = cmp(seg_tree[h], seg_tree[h ^ 1]);
                }
                if (idx > 0 && idx_to_clear[idx - 1] + 1 != idx_to_clear[idx])
                {
                    fb = front;
                }
                else
                {
                    fb = row[j - 1].x + 1;
                }
            }
            first_black[idx_to_clear[idx]] = row[j - 1].x + 1;
        }
        /*
        cout << "Cleared number:" << endl;
        for (auto x : cleared_in_line) {
            cout << x << " ";
        }
        cout << endl;
        */

        // Odd turn
        while (line_to_clear >= 0 && first_black[line_to_clear] >= n) {
            first_black[line_to_clear--] = n;
        }
        if (line_to_clear == -1) {
            break;
        }
        /*
        cout << "First black: " << endl;
        for (auto x : first_black) {
            cout << x << " ";
        }
        cout << endl;
        */
        ++turn;

        if (turn >= 2 * k + 2) {
            return -1;
        }
    }
    printf("%d", turn);
    return 0;
}

/*

4 4 5
1 2
2 2
1 3
1 1
0 2

4

6 3
9
0 0
2 0
4 0
1 1
3 1
5 1
0 2
2 2
4 2

8

4 4 4
0 0
3 1
0 2
2 0

6

4 4 2
2 0
2 2

4

*/
