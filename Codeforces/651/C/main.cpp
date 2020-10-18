#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        int n;
        cin >> n;
        if (n == 1)
        {
            cout << "FastestFinger" << endl;
            continue;
        }
        if (n % 2 == 1 || n == 2)
        {
            cout << "Ashishgup" << endl;
            continue;
        }
        int odd = n;
        while (odd % 2 == 0)
            odd /= 2;
        int even = n / odd;
        bool prime = true;
        for (int i = 2; i * i <= odd; ++i)
            if (odd % i == 0)
        {
            prime = false;
            break;
        }
        if (odd == 1)
        {
            cout << "FastestFinger" << endl;
            continue;
        }
        cout << (even > 2 || !prime ? "Ashishgup" : "FastestFinger") << endl;
    }
    return 0;
}
