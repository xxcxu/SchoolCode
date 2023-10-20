#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;
#define ep emplace
#define eb emplace_back
#define all(x) x.begin(), x.end()
FILE *fin, *fout, *ferr;
i32 read() {
  i32 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_CF1163F {
  bool _1;
  static const i32 N = 200005, M = N;
  i32 n, m, q, len, ignore;
  i64 dis1[N], disn[N];
  i32 vis[N], pre[N];
  i32 cnt = 1, head[N], ind[M], in[N], l[N], r[N];
  std::array<i32, 5> e[M << 1];
  void add(i32 u, i32 v, i32 id, i32 w) {
    e[++cnt] = {u, v, w, id, head[u]};
    head[u] = cnt;
    return void();
  }
  using Node = std::pair<i64, i32>;
  void dijkstra(i32 S, i64 *d, i32 op) {
    std::memset(d, 0x3f, (n + 1) * sizeof(i64));
    std::memset(vis, 0, sizeof vis);
    std::priority_queue<Node> q;
    q.ep(d[S] = 0LL, S);
    while (q.size()) {
      i32 x = q.top().second;
      q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (i32 i = head[x]; i; i = e[i][4]) {
        auto &[ignore, y, z, id, nxt] = e[i];
        if (chkmin(d[y], d[x] + z)) {
          if (op == 0) pre[y] = e[i][3];
          if (op == 1 && !in[y]) l[y] = l[x];
          if (op == 2 && !in[y]) r[y] = r[x];
          q.ep(-d[y], y);
        }
      }
    }
    return void();
  }
  struct SegmentTree {
    i64 tr[M << 2];
    SegmentTree() { std::memset(tr, 0x3f, sizeof tr); }
    #define ls (x << 1) 
    #define rs (x << 1 | 1)
    void change(i32 x, i32 l, i32 r, i32 ql, i32 qr, i64 v) {
      if (ql > qr) return void();
      if (ql <= l && r <= qr)
        return chkmin(tr[x], v), void();
      i32 mid((l + r) >> 1);
      if (ql <= mid) change(ls, l, mid, ql, qr, v);
      if (qr > mid) change(rs, mid + 1, r, ql, qr, v);
      return void();
    }
    i64 query(i32 x, i32 l, i32 r, i32 p) {
      if (l == r)
        return tr[x];
      i32 mid((l + r) >> 1);
      i64 ans = tr[x];
      if (p <= mid) chkmin(ans, query(ls, l, mid, p));
      else chkmin(ans, query(rs, mid + 1, r, p));
      return ans;
    }
  } seg;
  bool _2;
  void solve() {
    i32 now = 1;
    l[1] = r[1] = 0;
    in[1] = true;
    for (i32 i = 1; now != n; ++i) {
      i32 eg = pre[now];
      auto &[u, v, w, id, nxt] = e[eg * 2];
           if (now == u) now = v;
      else if (now == v) now = u;
      ++len;
      in[now] = true;
      l[now] = r[now] = i;
      ind[eg] = i;
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read(), q = read();
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      add(u, v, i, w), add(v, u, i, w);
    }
    i64 Start_Time_Without_Read = clock();
    dijkstra(n, disn, 0);
    solve();
    dijkstra(1, dis1, 1);
    dijkstra(n, disn, 2);
    for (i32 i = 1; i <= m; ++i) {
      auto &[u, v, w, id, nxt] = e[i * 2];
      if (!ind[i]) {
        seg.change(1, 1, len, l[u] + 1, r[v], dis1[u] + disn[v] + w);
        seg.change(1, 1, len, l[v] + 1, r[u], dis1[v] + disn[u] + w);
      }
    }
    while (q--) {
      static i32 t, _w;
      t = read(), _w = read();
      i64 ans = dis1[n];
      if (ind[t]) {
        ans = ans - e[t * 2][2] + _w;
        if (_w > e[t * 2][2])
          ans = std::min(ans, seg.query(1, 1, len, ind[t]));
      } else {
        ans = std::min(ans, dis1[e[t * 2][0]] + disn[e[t * 2][1]] + _w);
        ans = std::min(ans, dis1[e[t * 2][1]] + disn[e[t * 2][0]] + _w);
      }
      fprintf(fout, "%lld\n", ans);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1163F::main(), 0; }