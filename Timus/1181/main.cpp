#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <array>
#include <algorithm>

using namespace std;

enum class Color
{
    kRed = 0,
    kGreen,
    kBlue
};

Color char2color(char c)
{
    if (c == 'R')
        return Color::kRed;
    if (c == 'G')
        return Color::kGreen;
    return Color::kBlue;
}

struct Vertex
{
    Vertex(int idx, Color m) : id(idx), mark(m) {}
    Vertex() = default;

    int id = 0;
    Color mark = Color::kRed;
};

struct Polygon
{
    Polygon(std::vector<Vertex>&& v, array<int, 3> c)
        : ln(v), cnt(c) {}

    vector<Vertex> ln;
    array<int, 3> cnt;
};

deque<Polygon> q;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<Vertex> poly;
    array<int, 3> cnt = {0};
    for (size_t i = 0; i < s.size(); ++i)
    {
        poly.emplace_back(i + 1, char2color(s[i]));
        cnt[static_cast<int>(char2color(s[i]))]++;
    }
    q.emplace_back(move(poly), cnt);
    vector<pair<int, int>> res;
    while (!q.empty())
    {
        const vector<Vertex>& p = q.front().ln;
        const array<int, 3>& c = q.front().cnt;
        /*
        cout << "Polygon:" << endl;
        for (auto pt : p)
        {
            cout << pt.id << " ";
        }
        cout << endl;
        cout << "c = " << "[ " << c[0] << ", " << c[1] << ", " << c[2] << "]" << endl;
        */
        if (p.size() == 3)
        {
            if (any_of(c.begin(), c.end(), [](int v) { return v != 1;}))
            {
                cout << 0 << endl;
                return 0;
            }
            q.pop_front();
            continue;
        }
        if (any_of(c.begin(), c.end(), [](int v) {return v == 0;}))
        {
            cout << 0 << endl;
            return 0;
        }
        Color min_color = Color::kRed;
        if (c[1] < c[0])
        {
            min_color = Color::kGreen;
        }
        else if (c[2] < c[static_cast<int>(min_color)])
        {
            min_color = Color::kBlue;
        }

        for (int i = 0; i < p.size(); ++i)
        {
            if (p[i].mark != min_color)
                continue;
            array<int, 3> left_cnt = {0};
            array<int, 3> right_cnt = c;
            int j = (i + 2) % p.size();
            left_cnt[static_cast<int>(p[i].mark)]++;
            left_cnt[static_cast<int>(p[(i + 1) % p.size()].mark)]++;
            left_cnt[static_cast<int>(p[j].mark)]++;
            right_cnt[static_cast<int>(p[(i + 1) % p.size()].mark)]--;
            bool found = false;
            while ((j + 1) % p.size() != i)
            {
                if (all_of(left_cnt.begin(), left_cnt.end(), [](int v) {return v > 0;}) &&
                    all_of(right_cnt.begin(), right_cnt.end(), [](int v) {return v > 0;}))
                {
                    found = true;
                    vector<Vertex> poly_left;
                    vector<Vertex> poly_right;
                    for (int t = i; t != (j + 1) % p.size(); t = (t + 1) % p.size())
                    {
                        poly_left.push_back(p[t]);
                    }
                    for (auto t = j; t != (i + 1) % p.size(); t = (t + 1) % p.size())
                    {
                        poly_right.push_back(p[t]);
                    }
                    q.emplace_back(move(poly_left), left_cnt);
                    q.emplace_back(move(poly_right), right_cnt);
                    res.push_back(make_pair(p[i].id, p[j].id));
                    break;
                }
                right_cnt[static_cast<int>(p[j].mark)]--;
                j = (j + 1) % p.size();
                left_cnt[static_cast<int>(p[j].mark)]++;
            }
            if (found)
            {
                break;
            }
        }

        q.pop_front();
    }
    cout << res.size() << endl;
    for (auto p : res)
    {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
