#include <iostream>

int main()
{
    long x, y;
    std::cin >> x >> y;
    if (x <= 0 || y <= 0 || (x + y) % 2 == 0)
      std::cout << x << " " << y;
    else
      std::cout << y << " " << x;
    return 0;
}
