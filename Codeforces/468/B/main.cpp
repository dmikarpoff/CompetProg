#include <iostream>

using namespace std;

int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    int last_rnd = 0;
    while (n > 1)
    {
        ++last_rnd;
        n >>= 1;
    }
    int rnd = 0;
    --a;
    --b;
    while (a != b)
    {
        ++rnd;
        a >>= 1;
        b >>= 1;
    }
    if (rnd == last_rnd)
        cout << "Final!";
    else
        cout << rnd;
    return 0;
}
