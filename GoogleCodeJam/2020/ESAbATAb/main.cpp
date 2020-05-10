#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void inverse(string& str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == '0')
        {
            str[i] = '1';
        }
        else if (str[i] == '1')
        {
            str[i] = '0';
        }
    }
}

int main()
{
    int T;
    int b;
    cin >> T >> b;
    for (int o = 1; o <= T; ++o)
    {
        string res(b, '?');
        string prev_res(b, '?');
        size_t equal_pos = -1;
        size_t different_pos = -1;
        size_t first_question = 0;
        int turn = 0;
        while (turn < 150)
        {
//            cout << "Equal pos = " << equal_pos << endl;
//            cout << "Diff pos = " << different_pos << endl;
            if (equal_pos != static_cast<size_t>(-1) && different_pos != static_cast<size_t>(-1))
            {

                cout << equal_pos + 1 << endl;
                char val;
                cin >> val;
                bool inversed = (res[equal_pos] != val);
                cout << different_pos + 1 << endl;
                cin >> val;
                bool reversed = (inversed ? res[different_pos] == val : res[different_pos] != val);
                if (inversed)
                {
                    inverse(res);
                }
                if (reversed)
                {
                    reverse(res.begin(), res.end());
                }
                turn += 2;
            }
            else if (equal_pos != static_cast<size_t>(-1) || different_pos != static_cast<size_t>(-1))
            {
                size_t idx = (equal_pos != -1 ? equal_pos : different_pos);
                cout << idx + 1 << endl;
                char val;
                cin >> val;
                if (val != res[idx])
                {
//                    cout << "Inversion required" << endl;
                    inverse(res);
//                    cout << res << endl;
                }
                cout << 1 << endl;
                cin >> val;
                turn += 2;
            }
            int reduction = turn % 10;
            for (int i = 0; i < 10 - reduction; ++i, ++turn)
            {
                if (i % 2 == 0)
                {
                    size_t idx = first_question + i / 2;
                    cout << idx + 1 << endl;
                    cin >> res[idx];
                }
                else
                {
                    size_t idx = b - 1 - i / 2 - first_question;
                    cout << idx + 1 << endl;
                    cin >> res[idx];
                    if (res[idx] == res[first_question + i / 2])
                    {
                        equal_pos = first_question + i / 2;
                        //cout << "Eq pos = " << equal_pos << endl;
                    }
                    else
                    {
                        different_pos = first_question + i / 2;
                        //cout << "Df pos = " << different_pos << endl;
                    }
                }
            }
            first_question = res.find('?');
//            cout << "res = " << res << endl;
            if (first_question == string::npos)
            {
                break;
            }
        }
        cout << res << endl;
        string response;
        cin >> response;
        if (response == "N")
        {
            return 0;
        }
    }
    return 0;
}
