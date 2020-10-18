#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <locale>
#include <algorithm>
#include <codecvt>
#include <unordered_set>

using namespace std;

vector<wstring> split(const wstring& line) {
    vector<wstring> res;
    size_t pos = 0;
    while (true) {
        auto next_pos = line.find(L'\t', pos);
        if (next_pos == wstring::npos) {
            break;
        }
        res.push_back(line.substr(pos, next_pos - pos));
        pos = next_pos + 1;
    }
    res.push_back(line.substr(pos, line.size() - pos));
    return res;
}

int main()
{
    string directory = "data\\hidden_task\\";
    locale emp;
    auto codec = locale{emp, new std::codecvt_utf8<wchar_t>{}};
    wifstream query_in(directory + "qid_query.tsv");
    query_in.imbue(codec);
    unordered_map<size_t, wstring> id_to_query;
    while (query_in.good()) {
        wstring line;
        getline(query_in, line);
        if (line.empty()) {
            continue;
        }
        auto v = split(line);
        if (v.size() != 2) {
            cout << "Wrong columns number" << endl;
            return -1;
        }
        size_t q_id = stoi(v[0]);
        id_to_query[q_id] = v[1];
    }
    unordered_map<wstring, size_t> url_to_host;
    wifstream host_in(directory + "hostid_url.tsv");
    host_in.imbue(codec);
    while(host_in.good()) {
        wstring line;
        getline(host_in, line);
        if (line.empty()) {
            continue;
        }
        auto v = split(line);
        if (v.size() != 2) {
            cout << "Wrong columns number" << endl;
            return -1;
        }
        size_t h_id = stoi(v[0]);
        url_to_host[v[1]] = h_id;
    }

    struct QueryReply {
        wstring url;
        double rel;
    };

    unordered_map<size_t, vector<QueryReply>> query_rate;
    wifstream rate_in(directory + "qid_url_rating.tsv");
    rate_in.imbue(codec);
    while (rate_in.good()) {
        wstring line;
        getline(rate_in, line);
        if (line.empty()) {
            continue;
        }
        auto v = split(line);
        if (v.size() != 3) {
            cout << "Wrong columns number" << endl;
            return -1;
        }
        size_t q_id = stoi(v[0]);
        double rel = stod(v[2]);
        query_rate[q_id].push_back(QueryReply{v[1], rel});
    }
    wofstream out("out.txt");
    out.imbue(codec);
    for (const auto& q : id_to_query) {
        vector<QueryReply>& replies = query_rate[q.first];
        if (replies.empty()) {
            cout << "Failure on query" << endl;
            return -1;
        }
        sort(replies.begin(), replies.end(), [](const auto& lhs, const auto& rhs) {return lhs.rel > rhs.rel;});
        int cnt = 0;
        unordered_set<size_t> used_hosts;
        double pFound = 0.0;
        double pLook[10];
        double pRel[10];
        for (const auto& rate: replies) {
            auto host_it = url_to_host.find(rate.url);
            if (host_it == url_to_host.end()) {
                cout << "Unknown host" << endl;
                return -1;
            }
            size_t host_id = host_it->second;
            if (used_hosts.find(host_id) == used_hosts.end()) {
                used_hosts.insert(host_id);
                if (cnt == 0) {
                    pLook[cnt] = 1.0;
                } else {
                    pLook[cnt] = 0.85 * pLook[cnt - 1] * (1 - pRel[cnt - 1]);
                }
                pRel[cnt] = rate.rel;
                pFound += pRel[cnt] * pLook[cnt];
                ++cnt;
                if (cnt == 10) {
                    break;
                }
            }
        }
        out << q.second << " " << pFound << endl;
    }
    return 0;
}
