#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    string tmp;
    getline(cin, tmp);
    getline(cin, tmp);
    stringstream ss(tmp);
    int v;
    vector<int64_t> w;
    int max_val = 1;
    while (ss >> v)
    {
        max_val *= 3;
        w.push_back(v);
    }
    if (max_val < n)
    {
        cout << "No" << endl;
        return 0;
    }
    vector<char> used(n + 1, 0);
    for (int i = 0; i < max_val; ++i)
    {
        int64_t sum = 0;
        int d = i;
        for (int j = 0; j < w.size(); ++j)
        {
            sum += (d % 3 - 1) * w[j];
            d /= 3;
        }
        if (sum > 0 && sum < used.size())
        {
            used[sum] = 1;
        }
    }
    for (int i = 1; i <=n; ++i)
    {
        if (used[i] == 0)
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}
