#include <iostream>

#include <cstdint>
#include <string>

int main()
{
    uint64_t lower = 1;
    uint64_t upper = 1;
    while (true)
    {
        std::cout << upper << std::endl;
        std::string respond;
        std::getline(std::cin, respond);
        if (respond == "ok")
        {
            break;
        }
        lower = upper + 1;
        upper *= 2;
    }
    while (lower != upper)
    {
        uint64_t mid = (lower + upper) / 2;
        std::cout << mid << std::endl;
        std::string respond;
        std::getline(std::cin, respond);
        if (respond == "ok")
        {
            upper = mid;
        }
        else
        {
            lower = mid + 1;
        }
    }
    std::cout << "! " << lower << std::endl;
}