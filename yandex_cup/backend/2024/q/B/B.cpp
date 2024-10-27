#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int n, m;
    std::cin >> n >> m;
    int64_t x[3];
    for (int i = 0; i < m; ++i)
    {
        std::cin >> x[i];
    }
    int64_t b[3];
    for (int i = 0; i < m; ++i)
    {
        std::cin >> b[i];
    }
    std::vector<int64_t> k[3];
    for (int i = 0; i < m; ++i)
    {
        k[i].push_back(1);
        for (int j = 1; j < n; ++j)
        {
            auto y = k[i].back();
            k[i].push_back(y * x[i] % 23);
        }
    }
    std::vector<int64_t> res(m, 0);
    for (;;)
    {
        bool found = true;
        for (int i = 0; i < m && found; ++i)
        {
            int64_t y = 0;
            for (int j = 0; j < m; ++j)
            {
                y = (y + k[i][j] * res[j]) % 23;
            }
            if (y != b[i])
            {
                found = false;
            }
        }
        if (found)
        {
            break;
        }
        ///////////
        res[0]++;
        for (int i = 0; i + 1 < res.size(); ++i)
        {
            if (res[i] < 23)
            {
                break;
            }
            res[i + 1]++;
            res[i] = 0;
        }
    }
    for (int i = 0; i < m; ++i)
    {
        std::cout << static_cast<char>(res[i] + 'a');
    }
    for (int i = 0; i < n - m; ++i)
        std::cout << 'a';
    std::cout << std::endl;
}