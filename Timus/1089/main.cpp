#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string line;
    vector<string> dict;
    for (;;)
    {
        getline(cin, line);
        if (line == "#")
        {
            break;
        }
        dict.push_back(line);
    }
    int cnt = 0;
    while (getline(cin, line))
    {
        line += '.';
        string cur_word;
        for (size_t o = 0; o < line.size(); ++o)
        {
            char c = line[o];
            if (c >= 'a' && c <= 'z')
            {
                cur_word += c;
            }
            else
            {
                for (size_t j = 0; j < dict.size(); ++j)
                {
                    if (dict[j].size() != cur_word.size())
                    {
                        continue;
                    }
                    int diff = 0;
                    for (size_t h = 0; h < cur_word.size(); ++h)
                    {
                        if (cur_word[h] != dict[j][h])
                        {
                            diff++;
                            if (diff > 1)
                            {
                                break;
                            }
                        }
                    }
                    if (diff == 1)
                    {
                        cur_word = dict[j];
                        cnt++;
                        break;
                    }
                }
                cout << cur_word;
                cur_word = "";
                if (o + 1 != line.size())
                {
                    cout << c;
                }
            }
        }
        cout << endl;
    }
    cout << cnt << endl;
    return 0;
}
