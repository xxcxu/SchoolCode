#include <bits/stdc++.h>
static const int N = 1000005;
int n, d, cnt;
signed main() {
  int t; scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &d);
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
      int x; scanf("%d", &x);
      if (x == 1) ++cnt;
    }
    if (d == 1) {
      if ((n % 3 == 0) && (cnt == n)) puts("No");
      else puts("Yes");
    } else {
      if (((n % 3 == 0) && (cnt == n - 1)) || ((n % 3 == 1) && (cnt >= n - 1))) puts("No");
      else puts("Yes");
    }
  }
  return 0;
}