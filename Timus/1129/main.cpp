#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum class Color
{
    kUnknown = 0,
    kYellow,
    kGreen
};

struct Door
{
    explicit Door(int d) : dst(d) {}

    int dst = -1;
    Color c = Color::kUnknown;
};

vector<vector<Door>> adj;
vector<int> p;
vector<int> pw;

void dfs(int x) {
    for (auto d : adj[x]) {
        if (p[d.dst] == -1 && d.c == Color::kUnknown) {
            p[d.dst] = x;
            dfs(d.dst);
        }
    }
}

void ham_dfs(int x) {
    if (pw[x] == 0)
        return;
    for (auto& d : adj[x]) {
        if (d.c == Color::kUnknown) {
            d.c = Color::kGreen;
            pw[d.dst]--;
            pw[x]--;
            for (auto& b : adj[d.dst]) {
                if (b.dst == x && b.c == Color::kUnknown) {
                    b.c = Color::kYellow;
                    break;
                }
            }
            ham_dfs(d.dst);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    adj.resize(n + 1);
    pw.resize(n + 1, 0);
    for (int i = 0; i < n; ++i)
    {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j)
        {
            int val;
            cin >> val;
            adj[i + 1].emplace_back(val);
        }
        pw[i + 1] = m;
    }
    auto is_odd = [](int x) {return x % 2 == 1;};
    auto cnt = count_if(pw.begin(), pw.end(), is_odd);
    while (cnt > 0)
    {
        for (int i = 1; i <= n; ++i) {
            if (pw[i] % 2 == 1) {
                /*
                cout << "Starting search from odd " << i << " vertex" << endl;
                for (int j = 1; j <= n; ++j)
                {
                    cout << pw[j] << " ";
                }
                cout << endl;
                */
                p = vector<int>(n + 1, -1);
                p[i] = i;
                dfs(i);
                for (int j = i + 1; j <= n; ++j) {
                    if (pw[j] % 2 == 1 && p[j] != -1) {
                        // cout << "Another odd = " << j << endl;
                        int v = j;
                        while (p[v] != v) {
                            int u = p[v];
                            for (auto& d : adj[v]) {
                                if (d.dst == u && d.c == Color::kUnknown) {
                                    d.c = Color::kGreen;
                                    break;
                                }
                            }
                            for (auto& d : adj[u]) {
                                if (d.dst == v && d.c == Color::kUnknown) {
                                    d.c = Color::kYellow;
                                    break;
                                }
                            }
                            pw[u]--;
                            pw[v]--;
                            v = u;
                        }
                        break;
                    }
                }
            }
        }
        cnt = count_if(pw.begin(), pw.end(), is_odd);
    }
    // cout << "No odd vertex" << endl;
    for (int i = 1; i <= n; ++i) {
        if (pw[i] > 0) {
            // cout << "Looking for Hamilton cycle from " << i << endl;
            ham_dfs(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (auto d : adj[i]) {
            switch (d.c) {
            case Color::kYellow:
                cout << "Y ";
                break;
            case Color::kGreen:
                cout << "G ";
                break;
            default:
                cout << "U ";
                return -1;
            }
        }
        cout << endl;
    }
    return 0;
}
