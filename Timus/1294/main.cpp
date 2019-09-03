#include <iostream>
#include <cstdint>
#include <cmath>
#include <cstdio>
#include <iomanip>

using namespace std;

int main()
{
    int64_t ad, ac, bd, bc;
    cin >> ad >> ac >> bd >> bc;
    int64_t c1 = bc * bc + bd * bd;
    int64_t c2 = ac * ac + ad * ad;
    int64_t b1 = 2 * bc * bd;
    int64_t b2 = 2 * ac * ad;
    if (b1 == b2)
    {
        cout << "Impossible." << endl;
        return 0;
    }
    double cd = static_cast<double>(c1 * b2 - b1 * c2) / (b2 - b1);
    /*
    if ((c1 * b2 - b1 * c2) * (b2 - b1) < 0)
    {
        cout << "Impossible." << endl;
        return 0;
    }
    */
    cd = sqrt(cd);
    cout << "Distance is " << fixed << setprecision(0);
    cout << cd * 1000.0 << " km." << endl;
    return 0;
}
