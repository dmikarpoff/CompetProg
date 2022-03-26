#include <iostream>

using namespace std;

string parse(const string& x)
{
    int i = 0;
    string res;
    while (i < x.size())
    {
        if (x[i] == 'z')
        {
            res += '0';
            i += 4;
        }
        else
        {
            res += '1';
            i += 3;
        }
    }
    return res;
}

int main()
{
    string a, b;
    cin >> a >> b;
    string parsed_a = parse(a);
    string parsed_b = parse(b);
    if (parsed_a.size() < parsed_b.size())
    {
        parsed_a = string(parsed_b.size() - parsed_a.size(), '0') + parsed_a;
    }
    else if (parsed_a.size() > parsed_b.size())
    {
        parsed_b = string(parsed_a.size() - parsed_b.size(), '0') + parsed_b;
    }
    /*
    cout << parsed_a << endl;
    cout << parsed_b << endl;
    */
    if (parsed_a > parsed_b)
    {
        cout << '>' << endl;
    }
    else if (parsed_a < parsed_b)
    {
        cout << '<' << endl;
    }
    else
    {
        cout << "=" << endl;
    }
    return 0;
}
