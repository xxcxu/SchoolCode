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
namespace Solution_Of_HLP1916 {
  bool _1;
  static constexpr i32 N = 100005;
  i32 n, m, k, M;
  i32 a[N];
  bool _2;
  struct SegmentTree {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    struct TreeNode {
      i32 now, ans;
      std::vector<std::pair<i32, i32>> pre, suf;
      TreeNode() {
        this->now = 0, this->ans = N + 1;
        this->pre.clear(), this->suf.clear();
      }
      TreeNode(i32 x) {
        this->now = a[x];
        if (this->now == M) this->ans = 1;
        else this->ans = N + 1;
        this->pre.clear();
        this->suf.clear();
        this->pre.eb(a[x], x);
        this->suf.eb(a[x], x);
      }
    } tr[N << 2];
    void pushup(i32 x) {
      const TreeNode &lson = tr[ls], &rson = tr[rs];
      tr[x] = TreeNode();
      tr[x].now = lson.now | rson.now;
      tr[x].ans = std::min(lson.ans, rson.ans);
      tr[x].pre = lson.pre;
      i32 now = lson.now;
      for (auto it : rson.pre)
        if ((it.first & now) != it.first) {
          now |= it.first;
          tr[x].pre.eb(now, it.second);
        }
      tr[x].suf = rson.suf;
      now = rson.now;
      for (auto it : lson.suf)
        if ((it.first & now) != it.first) {
          now |= it.first;
          tr[x].suf.eb(now, it.second);
        }
      i32 nn = lson.suf.size(), mm = rson.pre.size();
      for (i32 i = nn - 1, j = 0; j < mm; ++j) {
        if ((lson.suf[i].first | rson.pre[j].first) != M) continue;
        while (((lson.suf[i - 1].first | rson.pre[j].first) == M) && i > 0) --i;
        tr[x].ans = std::min(tr[x].ans, rson.pre[j].second - lson.suf[i].second + 1);
      }
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      if (l == r) {
        tr[x] = TreeNode(l);
        return void();
      }
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    void change(i32 x, i32 l, i32 r, i32 p, i32 v) {
      if (l == r) {
        a[l] = 1 << (v - 1);
        tr[x] = TreeNode(l);
        return void();
      }
      i32 mid((l + r) >> 1);
      if (p <= mid) change(ls, l, mid, p, v);
      else change(rs, mid + 1, r, p, v);
      return pushup(x);
    }
  } seg;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("story.in", "r");
    fout = fopen("story.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), k = read(), m = read();
    M = (1 << k) - 1;
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) a[i] = 1 << (a[i] - 1);
    seg.build(1, 1, n);
    for (i32 i = 1; i <= m; ++i) {
      i32 op, p, v;
      op = read();
      if (op == 1) p = read(), v = read(), seg.change(1, 1, n, p, v);
      if (op == 2) {
        i32 t = seg.tr[1].ans;
        fprintf(fout, "%d\n", t == N + 1 ? -1 : t);
      }
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1916::main(), 0; }