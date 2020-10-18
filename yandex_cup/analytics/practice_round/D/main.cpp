#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    unordered_map<string, int> players;
    unordered_map<string, int> won;
    vector<pair<string, string>> games;
    for (int i = 0; i < n; ++i) {
        string a, b;
        cin >> a >> b;
        players[a]++;
        players[b]++;
        games.emplace_back(a, b);
    }
    auto level = [&players](const auto& name) {
        return players[name];
    };
    sort(games.begin(), games.end(), [&level](const auto& lhs, const auto& rhs) {
            return min(level(lhs.first), level(lhs.second)) <
                    min(level(rhs.first), level(rhs.second));
         });
    int cur_level = n / 2 + 1;
    for (int i = 1, j = 0; cur_level > 0; ++i) {
//        cout << "round = " << i << endl;
        for (int h = j; h < j + cur_level; ++h) {
            int mi = min(level(games[h].first), level(games[h].second));
            int ma = max(level(games[h].first), level(games[h].second));
            if (won[games[h].first] != i - 1 || won[games[h].second] != i - 1) {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
//            cout << mi << " " << ma << endl;
            if (cur_level != 1 && (mi != i || ma <= i)) {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
            auto winner = level(games[h].first) == ma ? games[h].first : games[h].second;
            won[winner]++;
        }
        j += cur_level;
        cur_level /= 2;
    }
    cout << games.back().first << " " << games.back().second << endl;
    return 0;
}
