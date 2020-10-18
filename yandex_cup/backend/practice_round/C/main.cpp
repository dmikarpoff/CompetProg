#include <iostream>

using namespace std;

int main()
{
    int n, k;
    cin >> k >> n;
    int vasya = 0;
    int petya = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (vasya < k && petya < k) {
            if (x % 3 == 0) {
                if (x % 5 != 0) {
                    petya++;
                }
            } else {
                if (x % 5 == 0) {
                    vasya++;
                }
            }
        }
    }
    if (vasya > petya)
        cout << "Vasya" << endl;
    else if (petya > vasya)
        cout << "Petya" << endl;
    else
        cout << "Draw" << endl;
    return 0;
}
