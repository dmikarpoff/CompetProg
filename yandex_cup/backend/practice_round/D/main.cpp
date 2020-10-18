#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int l = 1;
    int r = n;
    while (l != r) {
        int mid = (l + r) / 2;
        cout << mid << endl;
        int v;
        cin >> v;
        if (v == 0) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l << endl;
    int v;
    cin >> v;
    cout << "! " << (v == 0 ? l : l - 1) << endl;
    return 0;
}
