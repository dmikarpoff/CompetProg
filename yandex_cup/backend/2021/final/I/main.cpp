#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace std;

vector<string> tokenize(string line)
{
    vector<string> res;
    string cur_token;
    for (size_t i = 0; i < line.size(); ++i)
    {
        if (isalnum(line[i]))
        {
          cur_token += line[i];
        }
        else if (!cur_token.empty())
        {
            res.emplace_back(move(cur_token));
            cur_token = "";
        }
    }
    if (!cur_token.empty())
    {
        res.emplace_back(move(cur_token));
    }
    return res;
}

enum class Kind
{
    S = 0,
    H,
    D,
    C
};

Kind get_kind(char c)
{
    switch (c)
    {
    case 'S':
        return Kind::S;
    case 'H':
        return Kind::H;
    case 'D':
        return Kind::D;
    case 'C':
        return Kind::C;
    }
    assert(false);
}

struct Card
{
    Card(int v, Kind k) : value{v}, kind{k} {}

    int value;
    Kind kind;
};

bool operator<(Card lhs, Card rhs)
{
    return lhs.value < rhs.value;
}

bool is_straight_flush(const std::vector<Card>& hand)
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (hand[i].value + 1 != hand[i + 1].value || hand[i].kind != hand[i + 1].kind)
        {
            return false;
        }
    }
    return true;
}

pair<int, int> get_hand_strength(const vector<Card>& hand)
{
    int cnt[15] = {0};
    for (size_t i = 0; i < 5; ++i)
    {
        cnt[hand[i].value]++;
    }
    for (auto x : cnt)
    {
        cerr << x << " ";
    }
    cerr << endl;
    // straight flush
    if (is_straight_flush(hand))
    {
        cerr << "Straight flush" << endl;
        return {100, hand[4].value};
    }
    {
        // four of a kind
        auto i = find(begin(cnt), end(cnt), 4);
        if (i != end(cnt))
        {
            cerr << "Four of a kind" << endl;
            return {99, i - begin(cnt)};
        }
    }
    {
        // full house
        auto a = find(begin(cnt), end(cnt), 3);
        auto b = find(begin(cnt), end(cnt), 2);
        if (a != end(cnt) && b != end(cnt))
        {
            cerr << "Full house" << endl;
            return {98, a - begin(cnt)};
        }
    }
    {
        // flush
        bool l = true;
        for (auto c: hand)
        {
            if (c.kind != hand[0].kind)
            {
                l = false;
            }
        }
        if (l)
        {
            cerr << "Flush" << endl;
            int s = 0;
            for (size_t i = 0; i < 5; ++i)
            {
                s += s * 15 + hand[4 - i].value;
            }
            return {97, s};
        }
    }
    {
        bool straight = true;
        for (size_t i = 0; i < 4; ++i)
            if (hand[i].value + 1 != hand[i + 1].value)
        {
            straight = false;
        }
        if (straight)
        {
            cerr << "Straight" << endl;
            return {96, hand[4].value};
        }
    }
    {
        auto i = find(begin(cnt), end(cnt), 3);
        if (i != end(cnt))
        {
            cerr << "Set" << endl;
            return {95, i - begin(cnt)};
        }
    }
    {
        auto i = find(begin(cnt), end(cnt), 2);
        if (i != end(cnt))
        {
            auto j = find(i + 1, end(cnt), 2);
            if (j != end(cnt))
            {
                cerr << "Two pairs" << endl;
                return {92, (j - begin(cnt)) * 100 + (i - begin(cnt))};
            }
            else
            {
                cerr << "Pair" << endl;
                return {90, i - begin(cnt)};
            }
        }
    }
    return {1, hand[4].value};
}

int main()
{
    ifstream in("input.txt");
    string line;
    vector<Card> columns;
    columns.reserve(52);
    pair<int, int> best_hand{0, 0};
    vector<string> winners;
    while (getline(in, line, '\n'))
    {
        line.erase(remove_if(line.begin(), line.end(),
                             [](char c) {return c == ' ' || c == '\t';}),
                   line.end());
        if (line.empty() && !winners.empty())
        {
            sort(winners.begin(), winners.end());
            for (const auto& w: winners)
            {
                cout << w << " ";
            }
            cout << endl;
            winners.clear();
            best_hand = {0, 0};
            columns.clear();
            columns.reserve(52);
            continue;
        }
        auto tokens = tokenize(move(line));
        if (tokens.empty())
        {
            continue;
        }
        assert(tokens.size() == 53);
        if (columns.empty())
        {
            for (const auto& t : tokens)
            {
                if (t.size() < 2 || t.size() > 3)
                {
                    continue;
                }
                if (t.size() == 3)
                {
                    columns.emplace_back(10, get_kind(t[2]));
                    continue;
                }
                int val = 0;
                switch (t[0])
                {
                case 'J':
                    val = 11;
                    break;
                case 'Q':
                    val = 12;
                    break;
                case 'K':
                    val = 13;
                    break;
                case 'A':
                    val = 14;
                    break;
                default:
                    val = t[0] - '0';
                }
                assert(val > 0 && val < 15);
                columns.emplace_back(val, get_kind(t[1]));
            }
            continue;
        }
        assert(columns.size() == 52);
        std::vector<Card> hand;
        auto name = tokens[0];
        for (size_t i = 1; i < tokens.size(); ++i)
            if (tokens[i] == "1")
        {
            hand.push_back(columns[i - 1]);
        }
        assert(hand.size() == 5);
        sort(hand.begin(), hand.end());
        pair<int, int> s = get_hand_strength(hand);
        if (s > best_hand)
        {
            winners.clear();
            best_hand = s;
        }

        if (s >= best_hand)
        {
            winners.push_back(name);
        }
    }
    if (!winners.empty())
    {
        sort(winners.begin(), winners.end());
        for (const auto& w: winners)
        {
            cout << w << " ";
        }
        cout << endl;
    }
    return 0;
}
