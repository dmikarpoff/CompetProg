#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a)
      cin >> x;
    sort(a.begin(), a.end());
    for (auto i = a.rbegin(); i != a.rend(); ++i)
      cout << *i << endl;
    return 0;
}
