#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    int k;
    cin >> k;
    int s = 0;
    vector<int> a;
    a.reserve(k);
    for (int i = 0; i < k; ++i)
    {
        int v;
        cin >> v;
        a.push_back(v);
        s += v;
    }
    vector<int> b;
    b.reserve(k);
    int min_count = 0;
    for (int i = 0; i < k; ++i)
    {
        int v;
        cin >> v;
        b.push_back(v);
        min_count += v;
    }
    vector<int> c;
    for (size_t i = 1; i <= s; ++i)
    {
        if (s % i == 0)
        {
            if (s / i < min_count)
            {
                break;
            }
            c.push_back(i);
        }
    }
    int res = 1;
    for (auto n : c)
    {
        bool valid = true;
        for (int j = 0; j < k; ++j)
        {
            if (b[j] * n  > a[j])
            {
                valid = false;
                break;
            }
        }
        if (valid)
        {
            res = n;
        }
    }

    cout << res << " " << s / res << endl;
    for (int i = 0; i < k; ++i)
    {
        a[i] -= b[i] * res;
    }
    int p = 0;
    string base;
    for (int j = 0; j < k; ++j)
    {
        for (int h = 0; h < b[j]; ++h)
        {
            base += to_string(j + 1) + " ";
        }
    }

    for (int i = 0; i < res; ++i)
    {
        printf(base.c_str());
        for (int j = min_count; j < s / res; ++j)
        {
            while (a[p] == 0)
            {
                ++p;
            }
            printf("%d ", p + 1);
            --a[p];

        }
        printf("\n");
    }
    return 0;
}
