#include <iostream>
#include <vector>
#include <unordered_map>

struct Pos
{
    Pos(int sh, int st) : ship(sh), stack(st) {}
    int ship;
    int stack;
};

int main()
{
    int n, h;
    std::cin >> n >> h;
    std::vector<int> l(n);
    std::vector<Pos> map[101];
    for (auto& x : l)
        std::cin >> x;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < l[i]; ++j)
        {
            int s;
            std::cin >> s;
            for (int h = 0; h < s; ++h)
            {
                int d;
                std::cin >> d;
                map[d].emplace_back(i, j);
            }
        }
    }
    for (int d = 1; d <= 100; ++d)
    {
        size_t consumed = 0;
        const auto& dest = map[d];
        while (consumed < dest.size())
        {
            std::cout << "1 " << dest[consumed].ship + 1 << " " << dest[consumed].stack + 1 << " 0" << std::endl;
            ++consumed;
            if (consumed % h == 0)
            {
                std::cout << 3 << std::endl;
            }
        }
        if (consumed % h != 0)
        {
            std::cout << 3 << std::endl;
        }
    }
    std::cout << "0" << std::endl;
    return 0;
}