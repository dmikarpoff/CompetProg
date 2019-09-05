#include <stdio.h>

int main()
{
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    printf("YES\n");
    for (int i = 0; i < k; ++i) {
      int t;
      scanf("%d", &t);
      int sum = 0;
      for (int j = 0; j < t; ++j) {
        int v;
        scanf("%d", &v);
        sum += v;
      }
      printf("%d\n", sum % m + 1);
    }
    return 0;
}
