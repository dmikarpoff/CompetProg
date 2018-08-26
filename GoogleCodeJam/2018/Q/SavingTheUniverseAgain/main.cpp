#include <iostream>

using namespace std;

int estimate(const string& val)
{
    int res = 0;
    int c = 1;
    for (size_t i = 0; i < val.size(); ++i)
        if (val[i] == 'C')
            c <<= 1;
        else
            res += c;
//    cout << "Estimated to " << res << endl;
    return res;
}

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int d;
        string p;
        cin >> d >> p;
        int cnt = 0;
        for (int i = 0; i < p.size();  ++i)
            if (p[i] == 'S')
                cnt++;
        int sw = 0;
        if (cnt <= d)
        {
            while (estimate(p) > d)
            {
                for (size_t j = p.size() - 1; j > 0; --j)
                    if (p[j] == 'S' && p[j - 1] == 'C')
                    {
                        std::swap(p[j], p[j - 1]);
                        ++sw;
                        break;
                    }
            }
        }
        cout << "Case #" << o + 1 << ": ";
        if (cnt > d)
            cout << "IMPOSSIBLE" << endl;
        else
        {
            cout << sw << endl;
        }
    }

    return 0;
}
