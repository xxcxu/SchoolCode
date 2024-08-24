#include <bits/stdc++.h>
const int N = 1e3 + 5;
int n, q; bool flag1;
class obj {public: int w, c, m;} a[N];
int f[N][N], h[N][N], g[N];
void Solve(int f[N][N], int g[]) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < N; ++j) g[j] = f[i - 1][j];
        for (int d = 1, t = a[i].m; t; d <<= 1) {
            if (t < d) d = t; t -= d;
            for (int j = N - 1; j >= a[i].c * d; --j)
                g[j] = std::max(g[j], g[j - a[i].c * d] + a[i].w * d);
        }
        for (int j = 0; j < N; ++j) f[i][j] = g[j];
    }
}
signed main() {
    #ifdef ONLINE_JUDGE
        freopen("knapsack.in", "r", stdin);
        freopen("knapsack.out", "w", stdout);
    #endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &a[i].c, &a[i].w, &a[i].m);
    Solve(f, g);
    std::reverse(a + 1, a + n + 1);
	Solve(h, g);
    scanf("%d", &q);
    for (int i = 1, x, v; i <= q; ++i) {
        scanf("%d%d", &x, &v); ++ x; int ans = 0;
        for (int j = 0; j <= v; ++j) ans = std::max(ans, f[x - 1][j] + h[n - x][v - j]);
        printf("%d\n", ans);
    } return 0;
}