#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int user_limit, service_limit, duration;
    vector<int> all_req;
    map<int, vector<int>> user_req;
    cin >> user_limit >> service_limit >> duration;
    for (;;)
    {
        int t;
        cin >> t;
        if (t == -1) {
            return 0;
        }
        int u_id;
        cin >> u_id;
        const auto& v = user_req[u_id];
        auto i1 = lower_bound(v.begin(), v.end(), t - duration);
        auto i2 = upper_bound(v.begin(), v.end(), t);
        auto req_num = i2 -i1;
//        cout << "# u_r =  " << req_num << endl;
        if (req_num >= user_limit) {
            cout << 429 << endl;
            continue;
        }
        i1 = lower_bound(all_req.begin(), all_req.end(), t - duration);
        i2 = upper_bound(all_req.begin(), all_req.end(), t);
        req_num = i2 - i1;
//        cout << "# r =  " << req_num << endl;
        if (req_num >= service_limit) {
            cout << 503 << endl;
            continue;
        }
        all_req.push_back(t);
        user_req[u_id].push_back(t);
        cout << 200 << endl;
    }

    return 0;
}
