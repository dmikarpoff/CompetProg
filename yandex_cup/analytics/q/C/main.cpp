#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

map<string, vector<string>> adj;
set<string> used;
vector<set<string>> components;

void dfs(const string& v) {
    used.insert(v);
    for (const auto& u : adj[v]) {
        if (used.find(u) == used.end()) {
            used.insert(u);
            components.back().insert(u);
            dfs(u);
        }
    }
}

int main()
{
    ifstream in("logs.csv");
    string line;
    vector<pair<string, string>> data;
    while(getline(in, line)) {
        int pos = line.find(',');
        if (pos == string::npos) {
            cout << "Fuck this! Fuck that!";
            return -1;
        }
        string email = line.substr(0, pos);
        string phone = line.substr(pos + 1, line.size() - pos);
        adj[email].push_back(phone);
        adj[phone].push_back(email);
        data.emplace_back(email, phone);
    }
    for (const auto& p : adj) {
        if (used.find(p.first) == used.end()) {
            components.emplace_back();
            components.back().insert(p.first);
            dfs(p.first);
        }
    }
    vector<int> cnt(components.size(), 0);
    for (auto d : data) {
        for (size_t i = 0; i < components.size(); ++i) {
            if (components[i].find(d.first) != components[i].end() || components[i].find(d.second) != components[i].end()) {
                assert(components[i].find(d.first) != components[i].end() && components[i].find(d.second) != components[i].end());
                cnt[i] += 1;
            }
        }
    }
    for (auto c : cnt) {
        if (c > 1)
        cout << c << " ";
    }
    cout << accumulate(cnt.begin(), cnt.end(), 0) << endl;
    cout << *max_element(cnt.begin(), cnt.end()) << endl;
    return 0;
}
