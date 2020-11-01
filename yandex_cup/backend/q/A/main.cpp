#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct Date {
    int y;
    int m;
    int d;

    int day_of_week;
};

int kDayInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(int y) {
    if (y % 4 != 0) {
        return false;
    }
    return y % 100 != 0 || y % 400 == 0;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.y < rhs.y)
        return true;
    if (lhs.y > rhs.y)
        return false;
    if (lhs.m < rhs.m)
        return true;
    if (lhs.m > rhs.m)
        return false;
    if (lhs.d < rhs.d)
        return true;
    return false;
}
Date operator++(Date& d) {
    d.d += 1;
    int day_in_month = kDayInMonth[d.m];
    if (d.m == 2 && isLeap(d.y)) {
        ++day_in_month;
    }
    if (d.d > day_in_month) {
        d.d = 1;
        d.m += 1;
        if (d.m > 12) {
            d.m = 1;
            d.y += 1;
        }
    }
    d.day_of_week = (d.day_of_week + 1) % 7;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.y == rhs.y && lhs.m == rhs.m && lhs.d == rhs.d;
}

string toString(const Date& d) {
    char buf[20];
    sprintf(buf, "%02d-%02d-%02d", d.y, d.m, d.d);
    return buf;
}

int main()
{
    string interval;
    cin >> interval;
    Date from, to;
    scanf("%d-%d-%d %d-%d-%d", &from.y, &from.m, &from.d, &to.y, &to.m, &to.d);
    Date original_to = to;
    ++to;
    Date cur_interval_start{1999, 12, 31};
    vector<pair<Date, Date>> intervals;
//    cout << "Iterating over dates" << endl;
    for (Date i{1999, 12, 31, 4}, prev{1999, 12, 30, 3}; i < to; ++i, ++prev) {
        if (i == from) {
            cur_interval_start = i;
            continue;
        }
        if (cur_interval_start < from) {
            continue;
        }

        if (interval == "WEEK") {
            if (i.day_of_week == 0) {
                intervals.emplace_back(cur_interval_start, prev);
                cur_interval_start = i;
            }
        } else if (interval == "MONTH") {
            if (i.d == 1) {
                intervals.emplace_back(cur_interval_start, prev);
                cur_interval_start = i;
            }
        } else if (interval == "QUARTER") {
            if (i.d == 1 && i.m % 3 == 1) {
//                cout << "Adding quarter" << endl;
                intervals.emplace_back(cur_interval_start, prev);
                cur_interval_start = i;
            }
        } else if (interval == "YEAR") {
            if (i.d == 1 && i.m == 1) {
                intervals.emplace_back(cur_interval_start, prev);
                cur_interval_start = i;
            }
        } else {
            if (i.d == 13 && i.day_of_week == 4) {
                intervals.emplace_back(cur_interval_start, prev);
                cur_interval_start = i;
            }
        }
    }
//    cout << "End of iterations" << endl;

    if ((intervals.empty() || !(intervals.back().first == cur_interval_start)) && !(cur_interval_start < from))
    {
        intervals.emplace_back(cur_interval_start, original_to);
    }

    cout << intervals.size() << endl;
    for (auto p : intervals) {
        cout << toString(p.first) << " " << toString(p.second) << endl;
    }

    return 0;
}
