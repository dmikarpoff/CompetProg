#include <iostream>
#include "json.hpp"
#include <queue>
#include <set>

using namespace std;

int main()
{
    string line;
    getline(cin, line);
    auto our_employee = nlohmann::json::parse(line);
    auto input_json = nlohmann::json::parse(cin);
    std::vector<nlohmann::json> output_vec;
    for (auto& elem: input_json)
    {
        nlohmann::json output_elem;
        if (!elem.contains("base-info") || !elem["base-info"].contains("description"))
        {
            output_elem["description"] = nlohmann::json{};
        }
        else
        {
            output_elem["description"] = elem["base-info"]["description"];
        }

        output_elem["index"] = elem.contains("index") ? elem["index"] : nlohmann::json{};

        set<nlohmann::json> reviewers_list;
        if (elem.contains("reviewers"))
        {
            queue<nlohmann::json*> q;
            for (auto& r : elem["reviewers"])
            {
                q.push(&r);
            }
            while (!q.empty())
            {
                auto x = q.front();
                q.pop();
                if (x->is_object() && x->contains("name"))
                {
                    reviewers_list.insert((*x)["name"]);
                }
                if (x->is_object() || x->is_array())
                {
                    for (auto& y: *x)
                        q.push(&y);
                }
            }
        }
        for (auto& x: our_employee)
            reviewers_list.erase(x);

        output_elem["reviewers"] = reviewers_list;

        vector<nlohmann::json> work_list;
        if (elem.contains("works"))
        {
            for (auto& w: elem["works"])
            {
                if (!w.contains("author") || !w["author"].is_string() || !w.contains("charters"))
                {
                    work_list.clear();
                    break;
                }
                for (auto& c : w["charters"])
                {
                    nlohmann::json::object_t obj;
                    obj[w["author"]] = c;
                    work_list.emplace_back(move(obj));
                }
            }
        }
        output_elem["works"] = work_list;

        vector<nlohmann::json> authors_vec;
        authors_vec.push_back(elem.contains("author") ? elem["author"] : nlohmann::json{});
        if (elem.contains("co-authors") && (elem["co-authors"].is_array() || elem["co-authors"].is_object()))
        {
            for (auto& x: elem["co-authors"])
                authors_vec.push_back(x);
        }
        output_elem["authors"] = authors_vec;

        vector<nlohmann::json> range_vec;
        if (elem.contains("values"))
        {
            auto vals = elem["values"];
            if (vals.is_array())
            {
                if (vals.empty())
                {
                    range_vec = {nlohmann::json{}, nlohmann::json{}};
                }
                else
                {
                    range_vec.push_back(elem["values"].back());
                    range_vec.push_back(elem["values"].front());
                }
            }
        }
        else
        {
            range_vec = {nlohmann::json{}, nlohmann::json{}};
        }
        output_elem["range"] = range_vec;

        if (!elem.contains("time") || !elem["time"].is_array() || elem["time"].empty())
        {
            continue;
        }

        if (!elem["time"].back().is_number() || ! elem["time"].front().is_number())
        {
            continue;
        }

        if (elem["time"].back().is_number_float() || elem["time"].back().is_number_float()
            || (elem.contains("price") && elem["price"].is_number_float()))
        {
            double cost = elem["time"].back().get<double>() - elem["time"].front().get<double>();
            cost *= elem.contains("price") ? elem["price"].get<double>() : 5.0;
            output_elem["cost"] = cost;
        }
        else
        {
            int64_t cost = elem["time"].back().get<int>() - elem["time"].front().get<int>();
            cost *= elem.contains("price") ? elem["price"].get<int>() : 5;
            output_elem["cost"] = cost;
        }

        if (!elem.contains("base-info") || !elem["base-info"].contains("reviewer.name"))
        {
            output_elem["reviewer"] = nlohmann::json{};
        }
        else
        {
            output_elem["reviewer"] = elem["base-info"]["reviewer.name"];
        }

        vector<nlohmann::json> last_vec;
        vector<nlohmann::json> remains_vec;

        if (!elem.contains("results"))
        {
            last_vec.push_back(nlohmann::json{});
        }
        else
        {
            bool next = false;
            auto& r = elem["results"];
            if (r.is_array())
            {
                for (auto& x : r)
                {
                    if (!x.is_object())
                    {
                        next = true;
                        break;
                    }
                }
                if (next)
                {
                    continue;
                }
                if (r.empty())
                {
                    last_vec.push_back(nlohmann::json{});
                }
                else
                {
                    last_vec.push_back(r.back().contains("url") ? r.back()["url"] : nlohmann::json{});
                    for (size_t i = 0; i + 1 < r.size(); ++i)
                    {
                        remains_vec.push_back(r[i].contains("url") ? r[i]["url"] : nlohmann::json{});
                    }
                }
            }
        }

        output_elem["last"] = last_vec;
        output_elem["remains"] = remains_vec;

        output_vec.emplace_back(move(output_elem));
    }
    cout << nlohmann::json(output_vec).dump(4) << endl;
    return 0;
}
