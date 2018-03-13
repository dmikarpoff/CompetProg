#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int x)
{
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

vector<int> primes;

std::vector<int> decompose(int x)
{
    std::vector<int> divs;
    for (size_t i = 0; i < primes[i] && x > primes[i]; ++i)
    {
        if (x % primes[i] == 0)
        {
            divs.push_back(primes[i]);
            while (x % primes[i] == 0)
                x /= primes[i];
        }
    }
    if (x > 1)
        divs.push_back(x);
    return divs;
}

int main()
{
    int x2;
    int min_x0 = x2;
    cin >> x2;
    for (size_t i = 2; i < 1000; ++i)
        if (is_prime(i))
            primes.push_back(i);

    vector<int> divs = decompose(x2);

    for (size_t i = 0; i < divs.size(); ++i)
    {
        int d = x2 / divs[i];
        int x1_min = max((d - 1) * divs[i] + 1, divs[i] + 1);
        int x1_max = x2;
        for (int x1 = x1_min; x1 <= x1_max; ++x1)
        {
            std::vector<int> divs_x1 = decompose(x1);
            for (size_t j = 0; j < divs_x1.size(); ++j)
            {
                int d = x1 / divs_x1[j];
                int x0 = max((d - 1) * divs_x1[j] + 1, divs_x1[j] + 1);
                if (x0 < min_x0)
                    min_x0 = x0;
            }
        }
    }
    cout << min_x0;
    return 0;
}
