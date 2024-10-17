#include <iostream>
#include <cstdint>

int main()
{
    int t;
    std::cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int n;
        std::cin >> n;
        int prev = 0;
        int64_t rising = 0;
        int64_t falling = 0;
        int64_t res = 0;
        std::cin >> prev;
        for (int i = 1; i < n; ++i)
        {
            int a;
            std::cin >> a;
            if (prev == a)
            {
                res += rising * falling;
                rising = 0;
                falling = 0;
                prev = a;
                continue;
            }
            if (a > prev)
            {
                if (falling > 0)
                {
                    res += rising * falling;
                    rising = 1;
                    falling = 0;
                }
                else
                {
                    ++rising;
                }
                prev = a;
                continue;
            }
            ++falling;
            prev = a;
        }
        res += rising * falling;
        std::cout << res << std::endl;
    }
}