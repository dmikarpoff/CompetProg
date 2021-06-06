#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <fstream>

using namespace std;

using Int128 = __uint128_t;

std::string decimal_string(Int128 x)
{
    if (x == 0)
    {
        return "0";
    }
    string res;
    while (x > 0)
    {
        res = static_cast<char>(x % 10 + '0') + res;
        x /= 10;
    }
    return res;
}

struct Fract
{
    Int128 nom = 0;
    Int128 denom = 1;

    Fract& operator+=(const Fract& other);
};

Int128 gcd(Int128 a, Int128 b)
{
    while (a > 0 && b > 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    return a + b;
}

void fract_reduce(Fract& f)
{
    auto d = gcd(f.nom, f.denom);
    f.nom /= d;
    f.denom /= d;
}

bool less_than_half(const Fract& f)
{
    return 2 * f.nom < f.denom;
}

Fract& Fract::operator+=(const Fract& other)
{
    auto g = gcd(other.denom, denom);
    // cout << "g = " << decimal_string(g) << endl;
    nom = nom * (other.denom / g) + (denom / g) * other.nom;
    denom *= (other.denom / g);
    fract_reduce(*this);
    return *this;
}

bool invert(string& s)
{
    for (auto& c : s)
    {
        c = (c == 'T' ? 'F' : 'T');
    }
    return true;
}

int main()
{
    std::ofstream out("a.txt");
    int t;
    cin >> t;
    std::vector<std::vector<Int128>> C(121, std::vector<Int128>(121, 0));
    for (size_t i = 0; i <= 120; ++i)
    {
        C[i][i] = C[i][0] = 1;
        for (size_t j = 1; j < i; ++j)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    for (int o = 1; o <= t; ++o)
    {
        int n, q;
        cin >> n >> q;
        vector<string> ans(n);
        vector<int> score(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> ans[i] >> score[i];
        }
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
        {
            if (i == n)
            {
                break;
            }
            string temp = ans[j];
            invert(temp);
            if (ans[i] == ans[j] || ans[i] == temp)
            {
                ans.erase(ans.begin() + j);
                score.erase(score.begin() + j);
                --j;
                --n;
            }
        }
        map<string, int> type_to_idx;
        switch (n)
        {
        case 1:
            type_to_idx = {{"T", 0}};
            break;
        case 2:
            type_to_idx = {{"TT", 0}, {"TF", 1}};
            break;
        case 3:
            type_to_idx = {{"TTT", 0}, {"TTF", 1}, {"TFT", 2}, {"TFF", 3}};
            break;
        default:
            return -1;
        }
        vector<int> f(n, 0);
        vector<vector<int>> k(n, vector<int>(type_to_idx.size(), 0));
        vector<int> cnt(4);
        for (int i = 0; i < q; ++i)
        {
            string type;
            for (int j = 0; j < n; ++j)
            {
                type += ans[j][i];
            }
            bool inverted = false;
            if (type[0] == 'F')
            {
                invert(type);
                inverted = true;
            }
            int idx = type_to_idx[type];
            ++cnt[idx];
            for (int j = 0; j < n; ++j)
            {
                if (ans[j][i] == 'T')
                {
                    if (inverted)
                    {
                        ++f[j];
                        --k[j][idx];
                    }
                    else
                    {
                        ++k[j][idx];
                    }
                }
                else
                {
                    if (inverted)
                    {
                        ++k[j][idx];
                    }
                    else
                    {
                        --k[j][idx];
                        ++f[j];
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            f[i] = score[i] - f[i];
        }

        string res;
        Fract res_exp{0u, 1u};
        map<string, std::pair<Fract, Fract>> p_map;
        switch (n)
        {
        case 1:
            {
                Fract p_t{1u, 2u};
                if (k[0][0] != 0)
                {
                    if (f[0] < 0)
                    {
                        f[0] = -f[0];
                        k[0][0] = -k[0][0];
                    }
                    p_t = Fract{static_cast<uint64_t>(f[0]), static_cast<uint64_t>(k[0][0])};
                    fract_reduce(p_t);
                }
                Fract p_f{p_t.denom - p_t.nom, p_t.denom};
                fract_reduce(p_f);
                p_map = {{"T", {p_t, p_f}}, {"F", {p_f, p_t}}};
            }
            break;
        case 2:
            {
                int64_t det = k[0][0] * k[1][1] - k[0][1] * k[1][0];
                int64_t det_0 = f[0] * k[1][1] - f[1] * k[0][1];
                int64_t det_1 = k[0][0] * f[1] - f[0] * k[1][0];
                if (det < 0)
                {
                    det = -det;
                    det_0 = -det_0;
                    det_1 = -det_1;
                }
                Fract p_tt = (det == 0 ? Fract{1, 2} : Fract{det_0, det});
                Fract p_tf = (det == 0 ? Fract{1, 2} : Fract{det_1, det});
                fract_reduce(p_tt);
                fract_reduce(p_tf);
                Fract p_ff{p_tt.denom - p_tt.nom, p_tt.denom};
                Fract p_ft{p_tf.denom - p_tf.nom, p_tf.denom};
                fract_reduce(p_ff);
                fract_reduce(p_ft);
                p_map = {{"TT", {p_tt, p_ff}}, {"FT", {p_ft, p_tf}},
                         {"TF", {p_tf, p_ft}}, {"FF", {p_ff, p_tt}}};
            }
            break;
        case 3:
        {
            Int128 denom = 0;
            Int128 nom0 = 0, nom1 = 0, nom2 = 0, nom3 = 0;
            /*
            cout << "Counts = [";
            for (int i = 0; i < 4; ++i)
            {
                cout << cnt[i] << " ";
            }
            cout << "]" << endl;
            */
            for (int t0 = 0; t0 <= cnt[0]; ++t0)
                for (int t1 = 0; t1 <= cnt[1]; ++t1)
                    for (int t2 = 0; t2 <= cnt[2]; ++t2)
            {
                int t3 = score[0] - t0 - t1 - t2;
                if (t3 < 0 || t3 > cnt[3])
                {
                    // cout << "Skip on wrong t3" << endl;
                    continue;
                }
                if (t0 + t1 + (cnt[2] - t2) + (cnt[3] - t3) != score[1])
                {
                    // cout << "Wrong score for 2nd student" << endl;
                    continue;
                }
                if (t0 + (cnt[1] - t1) + t2 + (cnt[3] - t3) != score[2])
                {
                    // cout << "Wrong score for 3rd student" << endl;
                    continue;
                }
                //cout << "T: " << t0 << " " << t1 << " " << t2 << " " << t3 << endl;
                nom0 += (t0 == 0 ? 0 : C[cnt[0] - 1][t0 - 1] * C[cnt[1]][t1] * C[cnt[2]][t2] * C[cnt[3]][t3]);
                nom1 += (t1 == 0 ? 0 : C[cnt[0]][t0] * C[cnt[1] - 1][t1 - 1] * C[cnt[2]][t2] * C[cnt[3]][t3]);
                nom2 += (t2 == 0 ? 0 : C[cnt[0]][t0] * C[cnt[1]][t1] * C[cnt[2] - 1][t2 - 1] * C[cnt[3]][t3]);
                nom3 += (t3 == 0 ? 0 : C[cnt[0]][t0] * C[cnt[1]][t1] * C[cnt[2]][t2] * C[cnt[3] - 1][t3 - 1]);
                denom = denom + C[cnt[0]][t0] * C[cnt[1]][t1] * C[cnt[2]][t2] * C[cnt[3]][t3];
                /*
                cout << "denom = " << decimal_string(denom) << endl;
                cout << "nom0 = " << decimal_string(nom0) << endl;
                cout << "nom1 = " << decimal_string(nom1) << endl;
                cout << "nom2 = " << decimal_string(nom2) << endl;
                cout << "nom3 = " << decimal_string(nom3) << endl;
                */
            }
            /*
            cout << "Final-----------" << endl;
            cout << "denom = " << decimal_string(denom) << endl;
            cout << "nom0 = " << decimal_string(nom0) << endl;
            cout << "nom1 = " << decimal_string(nom1) << endl;
            cout << "nom2 = " << decimal_string(nom2) << endl;
            cout << "nom3 = " << decimal_string(nom3) << endl;
            */
            Fract p_ttt{nom0, denom};
            Fract p_ttf{nom1, denom};
            Fract p_tft{nom2, denom};
            Fract p_tff{nom3, denom};
            Fract p_fff{denom - nom0, denom};
            Fract p_fft{denom - nom1, denom};
            Fract p_ftf{denom - nom2, denom};
            Fract p_ftt{denom - nom3, denom};
            p_map = {{"TTT", {p_ttt, p_fff}}, {"TTF", {p_ttf, p_fft}},
                     {"TFT", {p_tft, p_ftf}}, {"TFF", {p_tff, p_ftt}},
                     {"FFF", {p_fff, p_ttt}}, {"FFT", {p_fft, p_ttf}},
                     {"FTF", {p_ftf, p_tft}}, {"FTT", {p_ftt, p_tff}}};
            for (auto& p : p_map)
            {
                fract_reduce(p.second.first);
                fract_reduce(p.second.second);
            }
            break;
        }
        default:
            return -1;
        }

        for (int i = 0; i < q; ++i)
        {
            string type;
            for (int j = 0; j < n; ++j)
            {
                type += ans[j][i];
            }
            const auto& x = p_map[type];
            auto p = x.first;
            auto inv_p = x.second;
            if (less_than_half(p))
            {
                res += 'F';
                res_exp += inv_p;
            }
            else
            {
                res += 'T';
                res_exp += p;
            }
            fract_reduce(res_exp);
            // cout << "temp result =  " << decimal_string(res_exp.nom) << "/" << decimal_string(res_exp.denom) << endl;
        }

        cout << "Case #" << o << ": ";
        cout << res << " " << decimal_string(res_exp.nom) << "/" << decimal_string(res_exp.denom);
        cout << endl;
    }
    return 0;
}
