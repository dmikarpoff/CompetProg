#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int rate = 0;
    for (int i = 0; i < n; ++i)
    {
        int val;
        cin >> val;
        if (val == rate + 1)
        {
            rate++;
        }
        else if (val < rate)
        {
            rate = val;
        }
    }
    cout << rate << endl;
    return 0;
}
