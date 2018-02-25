#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    uint64_t k, d, t;
    cin >> k >> d >> t;
    uint64_t on = k;
    uint64_t off = (k / d) * d;
    if (off < k)
        off += d;
    off = off - on;
//    cout << on << " " << off << endl;
    uint64_t i = 2 * t / (2 * on + off);
    uint64_t rem = (2 * t) % (2 * on + off);
//    cout << i << " " << rem << endl;
    uint64_t res = 2 * i * (on + off);
    if (rem < 2 * on)
        res += rem;
    else
    {
        rem -= 2 * on;
        res += 2 * (on + rem);
    }
    cout << res / 2;
    if (res % 2)
        cout << ".5";
    return 0;
}
