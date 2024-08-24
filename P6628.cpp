#include <bits/stdc++.h>

#define int long long

const int N = 3e3 + 5;

template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}


template<typename T, typename ...Args>
void read(T &x, Args &...args) {
    read(x); read(args...);
}

int n, m, s, sum, ans;
int fa[N], deg[N], anc[N];
std::vector<int> Graph[N];
struct edge {int u, v, w; friend bool operator < (const edge a, const edge b) {return a.w < b.w;}};
int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

signed main() {
    read(n, m, s);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1, u, v; i <= m; ++i) {
        read(u, v);
        Graph[u].emplace_back(v);
        Graph[v].emplace_back(u);
        sum += std::abs(u - v);
        fa[find(u)] = find(v);
    }
    for (int i = 1; i <= n; ++i) anc[i] = find(i);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) fa[j] = j;
        Graph[s].emplace_back(i); Graph[i].emplace_back(s);
        fa[find(anc[s])] = find(anc[i]);
        int pre = 0; ans = sum;
        for (int j = 1; j <= n; ++j) {
            if ((int)Graph[j].size() & 1) {
                if (pre) {
                    ans += j - pre;
                    for (int k = pre; k < j; ++k) fa[find(anc[k])] = find(anc[j]);
                    pre = 0;
                } else pre = j;
            }
        }
        std::vector<edge> Edge;
        for (int j = 1; j <= n; ++j)
            if (Graph[j].size()) {
                if (pre && find(anc[j]) != find(anc[pre])) Edge.emplace_back((edge){anc[j], anc[pre], j - pre});
                pre = j;
            }
        std::sort(Edge.begin(), Edge.end());
        for (auto [u, v, w] : Edge)
            if (find(u) != find(v)) fa[find(u)] = find(v), ans += 2 * w;
        printf("%lld ", ans);
        Graph[s].pop_back(); Graph[i].pop_back();
    } return 0;
}