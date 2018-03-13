#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int r,c;
    cin >> r >> c;
    vector<string> fld(r);
    for (int i = 0; i < r; ++i)
        cin >> fld[i];
    for (size_t i = 0; i < r; ++i)
        for (size_t j = 0; j < c; ++j)
            if (fld[i][j] == 'S')
    {
        if (i < r - 1 && fld[i + 1][j] == 'W')
        {
            cout << "No";
            return 0;
        }
        if (i > 0  && fld[i - 1][j] == 'W')
        {
            cout << "No";
            return 0;
        }
        if (j < c - 1 && fld[i][j + 1] == 'W')
        {
            cout << "No";
            return 0;
        }
        if (j > 0  && fld[i][j - 1] == 'W')
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes" << endl;
    for (size_t i = 0; i < r; ++i)
    {
        for (size_t j = 0; j < c; ++j)
            if (fld[i][j] == '.')
                cout << "D";
            else
                cout << fld[i][j];
        cout << endl;
    }
    return 0;
}
