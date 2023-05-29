#include <cstdio>

using namespace std;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int a[1001];
    bool taken[1000];
    for (int i = 0; i <= n; ++i) {
        a[i] = 0;
        taken[i] = false;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        if (x > n || x < 0) {
            printf("NO");
            return 0;
        }
        a[x]++;
    }
    for (int i = 1; i <= n - 1; ++i) {
        if (a[i] > 2) {
            printf("NO");
            return 0;
        }
        if (a[i] == 2) {
            taken[i - 1] = true;
            taken[i] = true;
            a[i] = 0;
        }
    }
    if (a[0] >= 2 || a[n] >= 2) {
        printf("NO");
        return 0;
    }
    if ((a[0] >= 1 && taken[0])) {
        printf("NO");
        return 0;
    }
    if (a[0] == 1)
        taken[0] = true;
    for (int i = 1; i <= n - 1; ++i) {
        if (a[i] == 1) {
            if (!taken[i - 1]) {
                taken[i - 1] = true;
            } else if (!taken[i]) {
                taken[i] = true;
            } else {
                printf("NO");
                return 0;
            }
        }
    }
    if (a[n] == 1 && taken[n - 1]) {
        printf("NO");
        return 0;
    }
    printf("YES");
    return 0;
}
