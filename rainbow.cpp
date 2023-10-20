#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
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
namespace Solution_Of_rainbow {
  bool _1;
  static const i32 N = 200005, M = N;
  static const i32 P = 998244353;
  i32 n, m, ans[N];
  i32 a[N];
  i32 son[N], deg[N];
  bool vis[N];
  std::vector<i32> e[N], vec[N];
  struct dsu {
    i32 fa[N], size[N], eg[N];
    i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void reset(i32 n) {
      std::iota(fa + 1, fa + n + 1, 1);
      std::fill(size + 1, size + n + 1, 1);
      std::memset(eg + 1, 0, n * sizeof(i32));  
    }
    void merge(i32 x, i32 y) {
      i32 u = find(x), v = find(y);
      if (u == v) return ++eg[u], void();
      if (size[u] < size[v]) std::swap(u, v);
      fa[v] = u;
      size[u] += size[v];
      eg[u] += eg[v] + 1;
      return void();
    }
  } t;
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  struct SegmentTree {
    i32 tr[N << 2], mul_tag[N << 2], tag[N << 2], lazy[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    SegmentTree() { std::memset(tag, -1, sizeof tag); }
    void build(i32 x, i32 l, i32 r) {
      tag[x] = -1;
      lazy[x] = 0;
      mul_tag[x] = 0;
      tr[x] = 0;
      if (l == r)
        return void();
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return void();
    }
    void pushup(i32 x) {
      tr[x] = inc(tr[ls], tr[rs]);
      return void();
    }
    void pushtag(i32 x) {
      tr[x] = dec(0, tr[x]);
      lazy[x] = dec(0, lazy[x]);
      mul_tag[x] ^= 1;
      return void();
    }
    void pushtag(i32 x, i32 v, i32 l) {
      tr[x] = mul(v, l);
      tag[x] = v;
      mul_tag[x] = 0;
      lazy[x] = 0;
      return void();
    }
    void _pushtag(i32 x, i32 v, i32 l) {
      tr[x] = inc(tr[x], mul(v, l));
      lazy[x] = inc(lazy[x], v);
      return void();
    }
    void pushdown(i32 x, i32 l, i32 r) { 
      i32 mid((l + r) >> 1);
      if (tag[x] != -1) {
        pushtag(ls, tag[x], mid - l + 1);
        pushtag(rs, tag[x], r - mid);
        tag[x] = -1;
      }
      if (mul_tag[x]) {
        pushtag(ls);
        pushtag(rs);
        mul_tag[x] ^= 1;
      }
      if (lazy[x]) {
        _pushtag(ls, lazy[x], mid - l + 1);
        _pushtag(rs, lazy[x], r - mid);
        lazy[x] = 0;
      }
      return void();
    }
    void multi(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql > qr) return void();
      if (ql <= l && r <= qr)
        return pushtag(x);
      i32 mid((l + r) >> 1);
      pushdown(x, l, r);
      if (ql <= mid) multi(ls, l, mid, ql, qr);
      if (qr > mid) multi(rs, mid + 1, r, ql, qr);
      return pushup(x);
    }
    void change(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql > qr) return void();
      if (ql <= l && r <= qr)
        return _pushtag(x, v, r - l + 1);
      i32 mid((l + r) >> 1);
      pushdown(x, l, r);
      if (ql <= mid) change(ls, l, mid, ql, qr, v);
      if (qr > mid) change(rs, mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr, i32 v) {
      if (ql > qr) return void();
      if (ql <= l && r <= qr)
        return pushtag(x, v, r - l + 1);
      i32 mid((l + r) >> 1);
      pushdown(x, l, r);
      if (ql <= mid) modify(ls, l, mid, ql, qr, v);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    i32 query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql > qr) return 0;
      if (ql <= l && r <= qr) return tr[x];
      i32 mid((l + r) >> 1), ans = 0;
      pushdown(x, l, r);
      if (ql <= mid) ans = inc(ans, query(ls, l, mid, ql, qr));
      if (qr > mid) ans = inc(ans, query(rs, mid + 1, r, ql, qr));
      return ans;
    }
  } seg;
  void pre(i32 x, i32 fa) {
    vis[x] = true;
    for (i32 y : e[x])
      if (!vis[y])
        son[x] = y, pre(y, x);
    return void();
  }
  void dfs(i32 x, i32 l) {
    i32 t1 = seg.query(1, 1, M, 1, a[x]);
    i32 t2 = seg.query(1, 1, M, a[x] + 1, M);
    seg.multi(1, 1, M, 1, M);
    seg.change(1, 1, M, 1, a[x], inc(t1, t2));
    seg.modify(1, 1, M, a[x] + 1, M, 0);
    ans[l] = seg.query(1, 1, M, 1, a[x]);
    if (son[x]) dfs(son[x], l + 1);
    return void();
  }
  i32 chain(i32 x) {
    if (deg[x] == 0)
      return a[x];
    for (i32 st : vec[x]) {
      if (deg[st] == 1) {
        pre(st, 0);
        seg.build(1, 1, M);
        seg.modify(1, 1, M, 1, a[st], 1);
        dfs(son[st], 2);
        return ans[t.size[x]];
      }
    }
    return -1;
  }
  i32 circle(i32 x) {
    i32 min = INT_MAX;
    for (i32 st : vec[x]) chkmin(min, a[st]);
    for (i32 st : vec[x]) {
      if (a[st] == min) {
        pre(st, 0);
        i32 ret = 0;
        seg.build(1, 1, M);
        seg.modify(1, 1, M, 1, a[st], 1);
        dfs(son[st], 2);
        for (i32 i = t.size[x]; i >= 1; --i)
          if ((t.size[x] - i) & 1) ret = dec(ret, ans[i]);
          else ret = inc(ret, ans[i]);
        return ret;
      }
    }
    return -1;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    bool flag = true;
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    t.reset(n);
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
      ++deg[u], ++deg[v];
      t.merge(u, v);
    }
    i32 ans = 1;
    for (i32 i = 1; i <= n; ++i)
      vec[t.find(i)].eb(i);
    for (i32 i = 1; i <= n; ++i)
      if (t.find(i) == i) {
        if (t.eg[i] == t.size[i]) ans = mul(ans, circle(i));
        else ans = mul(ans, chain(i));
      }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_rainbow::main(), 0; }