#include <bits/stdc++.h>
static constexpr int N = 1e6 + 5, M = (1 << 22);
int n, ans, a[N], mx[M], mc[M];
auto Update(int x, int v) -> void {
    if (mx[x] < v) mc[x] = mx[x], mx[x] = v;
    else if (mc[x] < v) mc[x] = v;
}
auto main() -> decltype(0) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        Update(a[i], i);
    }
    for (int i = 0; i < 21; ++i)
        for (int j = 0; j < (1 << 21); ++j)
            if (!(j >> i & 1)) {
                Update(j, mx[j ^ (1 << i)]);
                Update(j, mc[j ^ (1 << i)]);
            }
    int sn = (1 << 21) - 1;
    for (int i = 0; i < (n - 2); ++i) {
        int c = a[i] ^ sn;
        int s = 0;
        for (int j = 21; ~j; --j)
            if (c >> j & 1) {
                s |= 1 << j;
                if (mc[s] <= i) s ^= 1 << j;
            }
        ans = std::max(ans, a[i] + s);
    }
    return printf("%d\n", ans), 0;
}