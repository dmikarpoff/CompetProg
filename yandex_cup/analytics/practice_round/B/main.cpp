#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<wstring, unordered_set<wstring>> dict;

int main()
{
    static locale emp;
    wifstream in("ticket_logs.csv");
    in.imbue(locale{emp, new std::codecvt_utf8<wchar_t>{}});
    int line_num = 0;
    while (in.good()) {
        wstring line;
        getline(in, line);
        if (line.empty()) {
            continue;
        }
        auto comma_pos = line.find(L',');
        if (comma_pos == wstring::npos || line.find(L',', comma_pos + 1) != wstring::npos) {
            wcout << L"Comma failure at line: " << line << L"\n";
            cout << line_num << endl;
            return -1;
        }
        dict[line.substr(0, comma_pos)].insert(line.substr(comma_pos + 1, line.size() - comma_pos - 1));
        ++line_num;
    }
    wofstream out("out.txt");
    out.imbue(locale(emp, new std::codecvt_utf8<wchar_t>));
    for (const auto& dict_elem : dict) {
        out << dict_elem.first << L"\n";
        unordered_set<wstring> unique_numbers;
        unordered_set<wstring> strange;
        for (wstring num: dict_elem.second) {
            num.erase(remove_if(num.begin(), num.end(), [&emp](wchar_t c) {return !isalnum(c, emp);}),
                      num.end());
            unique_numbers.insert(num);
            if (num.size() != 11 || any_of(num.begin(), num.end(), [&emp](wchar_t c) {return !isdigit(c, emp);})) {
                strange.insert(num);
            }
        }
        out << unique_numbers.size() << L"\n";
        out << L"Unique: [ ";
        for (const auto& x : unique_numbers) {
            out << x << L", ";
        }
        out << L"]\n";
        out << strange.size() << L"\n";
        out << L"Strange: [ ";
        for (const auto& x : strange) {
            out << x << L", ";
        }
        out << L"]\n";
    }
    return 0;
}
