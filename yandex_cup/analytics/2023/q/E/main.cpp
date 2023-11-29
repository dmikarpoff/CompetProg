#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_map<string, unordered_set<string>> d;

int main()
{
    std::ifstream in("logs.tsv");
    string line;
    getline(in, line);
    string token[5];
    while (in >> token[0])
    {
        for (int i = 1; i < 5; ++i)
        {
            in >> token[i];
        }

        if (token[2] != "like")
        {
            continue;
        }
        d[token[3]].insert(token[4]);
    }
    size_t l = 0;
    for (const auto& x: d)
    {
        l = max(l, x.second.size());
    }
    cout << l << endl;
    return 0;
}
