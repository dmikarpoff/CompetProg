#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

std::unordered_map<int, int> temp;

int main()
{
    int64_t sum_temp = 0;
    while (true) 
    {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (line[0] == '!')
        {
            return 0;
        }
        if (line[0] == '+')
        {
            char c;
            int id;
            double t;
            ss >> c >> id >> t;
            int itemp = static_cast<int>(std::round(t * 10));
            temp[id] = itemp;
            sum_temp += itemp;
            continue;
        }
        if (line[0] == '-')
        {
            char c;
            int id;
            ss >> c >> id;
            auto itemp = temp[id];
            temp.erase(id);
            sum_temp -= itemp;
            continue;
        }
        if (line[0] == '~')
        {
            char c;
            int id;
            double t;
            ss >> c >> id >> t;
            int itemp = static_cast<int>(std::round(t * 10));
            int old_temp = temp[id];
            temp[id] = itemp;
            sum_temp += itemp - old_temp;
            continue;
        }
        if (line[0] == '?')
        {

            if (temp.empty())
            {
                std::cout << "0.0" << std::endl;
            }
            std::cout << std::fixed << std::setprecision(9)
                << sum_temp / 10.0 / temp.size() << std::endl;
            continue;
        }
        return -1;
    }
    return 0;
}