#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

enum class Combination
{
    STRAIT_FLASH = 0,
    UNKNOWN
};

struct Hand
{
    Combination cmb = Combination::UNKNOWN;
    int severity = 0;
};

vector<string> parse_columns(const string& line)
{
    size_t lbound = line.find('|');
    size_t rbound = line.find('|', lbound + 1);
    vector<string> res;
    while (rbound != string::npos)
    {
        string t = string(line.begin() + lbound + 1, line.begin() + rbound);
        stringstream ss;
        ss.str(t);
        res.push_back("");
        ss >> res.back();
        lbound = rbound;
        rbound = line.find('|', lbound + 1);
    }
    return res;
}

pair<int, int> parse_card(const std::string& str)
{
    int value = 0;
    int kind = 0;
    if (str[0] >= '2' && str[0] <= '9')
    {
        value = str[0] - '2';
    }
    else
    {
        switch (str[0])
        {
        case '1':
            value = 8;
            break;
        case 'J':
            value = 9;
            break;
        case 'Q':
            value = 10;
            break;
        case 'K':
            value = 11;
            break;
        case 'A':
            value = 12;
            break;
        default:
            assert(false);
        }
    }
    switch (str.back())
    {
    case 'H':
        kind = 0;
        break;
    case 'D':
        kind = 1;
        break;
    case 'S':
        kind = 2;
        break;
    case 'C':
        kind = 3;
        break;
    default:
        assert(false);
    }
    return make_pair(value, kind);
}

Hand parse_hand(const std::vector<std::vector<char>>& cards)
{
    Hand res;
    for (int i = 0; i < 9; ++i)
    {
        for (int h = 0; h < 4; ++h)
        {
            bool str_flush = true;
            for (int k = 0; k < 5; ++k)
            {
                if (cards[i + k][h] == 0)
                {
                    str_flush = false;
                    break;
                }
            }
            if (str_flush)
            {
                res.cmb = Combination::STRAIT_FLASH;
                res.severity = max(i, res.severity);
            }
        }
    }
    if (res.cmb != Combination::UNKNOWN)
    {
        return res;
    }
    vector<char> cnt(13, 0);
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 4; ++j)
            cnt[i] += cards[i][j];
    }
    return res;
}

int main()
{
    string line;
    while (cin)
    {
        string splitter, header;
        getline(cin, splitter);
        getline(cin, header);
        auto columns = parse_columns(header);
        vector<pair<int, int>> column_values;
        for (size_t i = 1; i < columns.size(); ++i)
        {
            column_values.push_back(parse_card(columns[i]));
        }
        for (;;)
        {
            getline(cin, splitter);
            string row;
            getline(cin, row);
            if (row.empty())
            {
                break;
            }
            auto split_row = parse_columns(row);
            auto surname = split_row[0];
            vector<vector<char>> cur_cards(13, vector<char>(4, 0));
            cur_cards.resize(13, vector<char>(4, 0));
            for (size_t i = 1; i < split_row.size(); ++i)
            {
                if (split_row[i] == "1")
                {
                    cur_cards[column_values[i].first][column_values[i].second] = 1;
                }
            }
        }
    }
    return 0;
}
