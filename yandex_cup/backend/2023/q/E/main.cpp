#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <unordered_map>

using namespace std;

struct App
{
    size_t id;
    size_t vol;
};

bool operator<(const App& lhs, const App& rhs)
{
    return (lhs.vol > rhs.vol || (lhs.vol == rhs.vol && lhs.id < rhs.id));
}

struct Op
{
    size_t buy_id;
    size_t sell_id;
    double price;
    size_t vol;
};

vector<Op> ops;

int main()
{
    map<double, set<App>, greater<double>> sell;
    map<double, set<App>, greater<double>> buy;
    unordered_map<size_t, std::pair<set<App>::iterator, std::set<App>*>> cache;
    size_t last_id = 0;
    size_t n;
    cin >> n;
    string hz;
    getline(cin, hz);
    for (size_t o = 0; o < n; ++o)
    {
        string s;
        getline(cin, s);
        if (s.empty())
        {
            continue;
        }
        if (s[0] == 'A')
        {
            stringstream ss(s);
            string token, type;
            double price;
            size_t vol;
            ss >> token >> type >> price >> vol;
            if (token != "ADD")
            {
                return -1;
            }
            ++last_id;
            cout << last_id << endl;
            if (type == "BUY")
            {
                auto i = sell.lower_bound(price);
                for (;i != sell.end(); ++i)
                {
                    auto& p_set = i->second;
                    for (auto j = p_set.begin(); j != p_set.end();)
                    {
                        int t = min(vol, j->vol);
                        App a = *j;
                        a.vol -= t;
                        p_set.erase(j++);
                        cache.erase(a.id);
                        if (t > 0)
                        {
                            ops.push_back(Op{last_id, a.id, i->first, t});
                        }
                        if (a.vol > 0)
                        {
                            cache[a.id] = std::make_pair(p_set.insert(a).first, &p_set);
                        }
                        vol -= t;
                        if (vol == 0)
                        {
                            break;
                        }
                    }
                }
                if (vol > 0)
                {
                    auto &x = buy[price];
                    cache[last_id] = std::make_pair(x.insert(App{last_id, vol}).first, &x);
                }
            }
            else if (type == "SELL")
            {
                for (auto i = buy.begin(); i != buy.end() && i->first >= price; ++i)
                {
                    auto& s_set = i->second;
                    for (auto j = s_set.begin(); j != s_set.end();)
                    {
                        int t = min(vol, j->vol);
                        App a = *j;
                        a.vol -= t;
                        s_set.erase(j++);
                        cache.erase(a.id);
                        if (t > 0)
                        {
                            ops.push_back(Op{a.id, last_id, i->first, t});
                        }
                        if (a.vol > 0)
                        {
                            cache[a.id] = make_pair(s_set.insert(a).first, &s_set);
                        }
                        vol -= t;
                        if (vol == 0)
                        {
                            break;
                        }
                    }
                }
                if (vol > 0)
                {
                    auto& x = sell[price];
                    cache[last_id] = make_pair(x.insert(App{last_id, vol}).first, &x);
                }
            }
            else
            {
                return -1;
            }
            continue;
        }
        if (s[0] == 'G')
        {
            if (s != "GET")
            {
                return -1;
            }
            for (const auto& t : sell)
            {
                vector<App> app(t.second.begin(), t.second.end());
                sort(app.begin(), app.end(), [](const App& lhs, const App& rhs) {return lhs.id > rhs.id;});
                for (const auto& x: app)
                {
                    cout << x.id << " SELL " << fixed << setprecision(2) << t.first << " " << x.vol << endl;
                }
            }
            for (const auto& t : buy)
            {
                vector<App> app(t.second.begin(), t.second.end());
                sort(app.begin(), app.end(), [](const App& lhs, const App& rhs) {return lhs.id < rhs.id;});
                for (const auto& x: app)
                {
                    cout << x.id << " BUY " << fixed << setprecision(2) << t.first << " " << x.vol << endl;
                }
            }
            continue;
        }
        //=====================================
        if (s[0] == 'D')
        {
            stringstream ss(s);
            string token;
            size_t id;
            ss >> token >> id;
            if (token != "DELETE")
            {
                return -1;
            }
            auto it = cache.find(id);
            if (it == cache.end())
            {
                cout << "NOT FOUND" << endl;
            }
            else
            {
                it->second.second->erase(it->second.first);
                cache.erase(it);
                cout << "DELETED" << endl;
            }
            continue;
        }
        // =======================
        if (s[0] == 'S')
        {
            stringstream ss(s);
            string token;
            size_t num;
            ss >> token >> num;
            if (token != "SHOW_OPERATIONS")
            {
                return -1;
            }
            size_t from = 0;
            if (ops.size() >= num)
            {
                from = ops.size() - num;
            }
            for (size_t i = from; i < ops.size(); ++i)
                cout << ops[i].buy_id << " " << ops[i].sell_id << " " << fixed << setprecision(2) <<
                        ops[i].price << " " << ops[i].vol << endl;
        }
    }
    return 0;
}
