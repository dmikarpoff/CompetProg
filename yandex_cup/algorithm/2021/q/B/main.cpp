#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

string normal_tile(string tile)
{
    string min_tile = tile;
    for (size_t j = 0; j < 3; ++j)
    {
        tile = tile[3] + tile.substr(0, 3);
        min_tile = min(min_tile, tile);
    }
    return min_tile;
}

int main()
{
    int k;
    cin >> k;
    string dummy;
    // cin >> dummy;
    map<string, int> available_tile;
    for (size_t i = 0; i < k; ++i)
    {
        string line[2];
        cin >> line[0] >> line[1];
        // cout << line[0] << line[1];
        string tile = normal_tile(line[0] + line[1][1] + line[1][0]);
        available_tile[tile]++;
    }
    int r, c;
    cin >> r >> c;
    // cin >> dummy;
    map<string, int> req_tile;
    for (int i = 0; i < r; i += 2)
    {
        string line[2];
        cin >> line[0] >> line[1];
        for (size_t j = 0; j < c; j += 2)
        {
            string tile = normal_tile(line[0].substr(j, 2) + line[1][j + 1] + line[1][j]);
            req_tile[tile]++;
        }
    }
    for (const auto& p : req_tile)
    {
        if (p.second > available_tile[p.first])
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}
