#include <iostream>
#include <sstream>
#include <map>

using namespace std;

map<int, string> categ;

struct Offer
{
    int id;
    string name;
    string descr;
    int price;
};

map<int, Offer> min_price;
map<int, Offer> max_price;

int main()
{
    string s;
    bool categories = false;
    while (getline(cin, s))
    {
        if (s.empty())
        {
            continue;
        }
        if (s[0] != ' ')
        {
            categories = (s[0] == 'c');
            continue;
        }
        if (categories)
        {
            stringstream ss;
            string tmp;
            ss.str(s);
            int id;
            ss >> tmp >> tmp >> id;
            string name_line;
            getline(cin, name_line);
            auto pos = name_line.find(':');
            string name = string(name_line.begin() + pos + 1, name_line.end());
            categ[id] = name;
            continue;
        }
        stringstream ss;
        string tmp;
        ss.str(s);
        int id;
        ss >> tmp >> tmp >> id;
        int cat_id;
        getline(cin, s);
        stringstream ss1;
        ss1.str(s);
        ss1 >> tmp >> cat_id;
        getline(cin, s);
        auto pos = s.find(':');
        string name = string(s.begin() + pos + 1, s.end());
        getline(cin, s);
        pos = s.find(':');
        string descr = string(s.begin() + pos + 1, s.end());
        int price;
        getline(cin, s);
        stringstream ss2;
        ss2.str(s);
        ss2 >> tmp >> price;
        //cout << id << " " << cat_id << " " << name << " " << descr << " " << price << endl;
        Offer offer;
        offer.id = id;
        offer.name = name;
        offer.descr = descr;
        offer.price = price;
        auto min_it = min_price.find(cat_id);
        if (min_it == min_price.end() || min_it->second.price > price)
        {
            min_price[cat_id] = offer;
        }
        auto max_it = max_price.find(cat_id);
        if (max_it == max_price.end() || max_it->second.price < price)
        {
            max_price[cat_id] = offer;
        }
    }
    for (const auto& c: categ)
    {
        if (min_price.find(c.first) == min_price.end())
        {
            continue;
        }
        cout << "- id: " << c.first << endl;
        cout << "  name:" << c.second << endl;
        cout << "  minOffer:" << endl;
        auto min_offer = min_price[c.first];
        cout << "    id: " << min_offer.id << endl;
        cout << "    name:" << min_offer.name << endl;
        cout << "    description:" << min_offer.descr << endl;
        cout << "    price: " << min_offer.price << endl;

        cout << "  maxOffer:" << endl;
        auto max_offer = max_price[c.first];
        cout << "    id: " << max_offer.id << endl;
        cout << "    name:" << max_offer.name << endl;
        cout << "    description:" << max_offer.descr << endl;
        cout << "    price: " << max_offer.price << endl;
    }
    return 0;
}
