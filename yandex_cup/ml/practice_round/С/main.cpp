#include <iostream>
#include <string>
#include <numeric>
#include <codecvt>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int64_t kModulo = 500003;
vector<bool> counter(kModulo, false);

int main()
{
    ios_base::sync_with_stdio(false);
    locale empty;
    wcin.imbue(locale(empty, new codecvt_utf8<wchar_t>));
    int n;
    wcin >> n;
    wstring line;
    getline(wcin, line);
    for (int i = 0; i < n; ++i) {
        wstring line;
        getline(wcin, line);
        uint64_t h = 0;
        for (auto c : line) {
            h = h * 2047 + c;
        }
        counter[h % kModulo] = true;
    }
    wcout << count(begin(counter), end(counter), true) / 0.951 << endl;
    return 0;
}
