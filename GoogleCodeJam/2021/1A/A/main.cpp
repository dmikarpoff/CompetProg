#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool lt(const string& lhs, const string& rhs) {
    if (lhs.size() < rhs.size()) {
        return true;
    }
    if (lhs.size() > rhs.size()) {
        return false;
    }
    return lhs < rhs;
}

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o) {
        int n;
        cin >> n;
        string prev = "";
        int cost = 0;
        for (int i = 0; i < n; ++i) {
            string cur;
            cin >> cur;
            if (!lt(prev, cur)) {
                bool done = false;
                for (size_t j = 0; j < cur.size(); ++j) {
                    if (cur[j] > prev[j]) {
                        cost += prev.size() - cur.size();
                        cur.resize(prev.size(), '0');
                        done = true;
                        break;
                    }
                    if (cur[j] < prev[j]) {
                        cost += prev.size() - cur.size() + 1;
                        cur.resize(prev.size() + 1, '0');
                        done = true;
                        break;
                    }
                }
                if (!done) {
                    for (size_t j = prev.size() - 1; j >= cur.size(); --j) {
                        if (prev[j] != '9') {
                            cost += prev.size() - cur.size();
                            cur = prev;
                            cur[j] = static_cast<char>(prev[j] + 1);
                            for (size_t h = j + 1; h < cur.size(); ++h) {
                                cur[h] = '0';
                            }
                            done = true;
                            break;
                        }
                    }
                    if (!done) {
                        cost += prev.size() - cur.size() + 1;
                        cur.resize(prev.size() + 1, '0');
                    }
                }
            }
            prev = move(cur);
        }
        cout << "Case #" << o + 1 << ": ";
        cout << cost;
        cout << endl;
    }
    return 0;
}
