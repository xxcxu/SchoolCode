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
i32 read() {
  i32 t = 0, f = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
  for (; isdigit(ch); ch = getchar()) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_HLP140 {
  bool _1;
  static const i32 N = 200005;
  i32 n, m;
  i64 a[N], b[N], f[N];
  i32 l[N], r[N], x[N], y[N];
  std::vector<i32> vec[N];
  std::vector<std::pair<i32, i32>> vec2[N];
  bool _2;
  struct SegmentTree {
    i64 tr[N << 2], tag[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    SegmentTree() { std::memset(tr, 128, sizeof tr); }
    void pushup(i32 x) {
      tr[x] = std::max(tr[ls], tr[rs]);
      return void();
    }
    void pushtag(i32 x, i64 v) {
      tr[x] += v;
      tag[x] += v;
      return void();
    }
    void pushdown(i32 x) {
      if (tag[x]) {
        pushtag(ls, tag[x]);
        pushtag(rs, tag[x]);
        tag[x] = 0;
      }
      return void();
    }
    void change(i32 x, i32 l, i32 r, i32 p, i64 v) {
      if (l == r)
        return tr[x] = v, void();
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (p <= mid) change(ls, l, mid, p, v);
      else change(rs, mid + 1, r, p, v);
      return pushup(x);
    }
    void modify(i32 x, i32 l, i32 r, i32 ql, i32 qr, i64 v) {
      if (ql <= l && r <= qr)
        return pushtag(x, v);
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (ql <= mid) modify(ls, l, mid, ql, qr, v);
      if (qr > mid) modify(rs, mid + 1, r, ql, qr, v);
      return pushup(x);
    }
    i64 query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
      if (ql <= l && r <= qr) return tr[x];
      i64 ans = tr[0];
      i32 mid((l + r) >> 1);
      pushdown(x);
      if (ql <= mid) chkmax(ans, query(ls, l, mid, ql, qr));
      if (qr > mid) chkmax(ans, query(rs, mid + 1, r, ql, qr));
      return ans;
    }
  } seg;
  void main() {
    freopen("attack.in", "r", stdin);
    freopen("attack.out", "w", stdout);
    n = read(), m = read();
    i64 s = 0;
    for (i32 i = 1; i <= n; ++i) s += (a[i] = read());
    for (i32 i = 1; i <= m; ++i) l[i] = read(), r[i] = read(), x[i] = read(), y[i] = read();
    for (i32 i = 1; i <= m; ++i) vec[l[i]].eb(x[i]), vec[r[i] + 1].eb(-x[i]);
    std::multiset<i32> set;
    set.insert(0);
    for (i32 i = 1; i <= n; ++i) {
      for (i32 j : vec[i])
        if (j < 0) set.erase(set.find(-j));
        else set.insert(j);
      b[i] = *set.rbegin() + a[i];
    }
    for (i32 i = 1; i <= n; ++i) {
      vec2[l[i]].eb(l[i], -y[i]);
      vec2[r[i] + 1].eb(l[i], y[i]);
    }
    i64 ans = -s;
    seg.change(1, 1, n + 1, 1, -s);
    for (i32 i = 1; i <= n; ++i) {
      for (auto &[p, v] : vec2[i]) seg.modify(1, 1, n + 1, 1, p, v);
      f[i] = seg.query(1, 1, n + 1, 1, i) + b[i];
      seg.change(1, 1, n + 1, i + 1, f[i]);
      ans = std::max(ans, f[i]);
    }
    printf("%lld\n", ans);
    return void();
  }
}
signed main() { return Solution_Of_HLP140::main(), 0; }