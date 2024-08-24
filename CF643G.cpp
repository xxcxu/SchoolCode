#include <iostream>
#include <cstdio>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
using pii = std::pair<int, int>;
static const int N = 15e4 + 5, P = 1e2 + 5;
std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count() + 1);
int n, m, p, size;
int a[N], bel[N], tag[N], vis[P * N], cnt[P * N];
int val(int x) {return tag[bel[x]] ? tag[bel[x]] : a[x];}
signed main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    size = (int)std::sqrt(n);
    for (int i = 1; i <= n; ++i) bel[i] = (i - 1) / size + 1;
    while (m --) {
        static int op, l, r, x, y = 0;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &x);
            int p = bel[l], q = bel[r];
            if (tag[p]) for (int i = (p - 1) * size + 1; i <= p * size; ++i) a[i] = tag[p];
            if (tag[q]) for (int i = (q - 1) * size + 1; i <= q * size; ++i) a[i] = tag[q];
            tag[p] = tag[q] = 0;
            for (int i = p + 1; i <= q - 1; ++i) tag[i] = x;
            if (p != q) {
                for (int i = l; i <= p * size; ++i) a[i] = x;
                for (int i = (q - 1) * size + 1; i <= r; ++i) a[i] = x;
            } else for (int i = l; i <= r; ++i) a[i] = x;
        }
        if (op == 2) {
            ++ y;
            std::vector<pii> A;
            std::vector<int> randed;
            std::uniform_int_distribution<int> random(l, r);
            #define eb emplace_back
            for (int i = 1; i <= 666; ++i) {
                int x = val(random(gen));
                if (vis[x] != y) vis[x] = y, cnt[x] = 0, randed.eb(x);
                ++ cnt[x];
            }
            for (int x : randed) A.eb(cnt[x], x);
            std::sort(A.begin(), A.end(), std::greater<pii>());
            for (int i = 0; i < 5; ++i) A.eb(A[i]);
            printf("%d ", 100 / p);
            for (int i = 0; i < 100 / p; ++i) printf("%d ", A[i].second);
            puts("");
            #undef eb
        }
    } return 0;
}