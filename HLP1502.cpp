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
namespace Solution_Of_HLP1502 {
  bool _1;
  static const i32 N = 100005;
  i32 n, m, k, C, H;
  i64 c[N * 4], x[N * 2], y[N * 2], ans[N];
  struct Node {
    i32 x, y, op, id;
    Node() = default;
    Node(i32 x, i32 y, i32 op, i32 id = 0):
      x(x), y(y), op(op), id(id) {}
  } a[N * 2];
  struct TreeArray1 {
    i64 s[N * 4];
    void clear() { std::fill(s, s + k + 1, - C - H);}
    void add(i32 x, i64 v) {
      for (; x <= k; x += x & -x)
        chkmax(s[x], v);
      return void();
    }
    i64 ask(i32 x) {
      i64 ans = s[0];
      for (; x >= 1; x -= x & -x)
        chkmax(ans, s[x]);
      return ans;
    }
  } t1;
  struct TreeArray2 {
    i64 s[N * 4];
    void clear() { std::fill(s, s + k + 1, - C - H);}
    void add(i32 x, i64 v) {
      for (; x >= 1; x -= x & -x)
        chkmax(s[x], v);
      return void();
    }
    i64 ask(i32 x) {
      i64 ans = s[0];
      for (; x <= k; x += x & -x)
        chkmax(ans, s[x]);
      return ans;
    }
  } t2;
  bool _2;
  void discrete() {
    std::sort(c + 1, c + k + 1);
    k = std::unique(c + 1, c + k + 1) - c - 1;
    for (i32 i = 1; i <= n + m; ++i) x[i] = std::lower_bound(c + 1, c + k + 1, x[i]) - c;
    for (i32 i = 1; i <= n + m; ++i) y[i] = std::lower_bound(c + 1, c + k + 1, y[i]) - c;
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("theatre.in", "r");
    fout = fopen("theatre.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    C = read(), H = read();
    n = read();
    for (i32 i = 1; i <= n; ++i) {
      x[i] = read(), y[i] = read();
      c[++k] = x[i], c[++k] = y[i];
    }
    m = read();
    for (i32 i = 1; i <= m; ++i) {
      x[n + i] = read(), y[n + i] = read();
      c[++k] = x[n + i], c[++k] = y[n + i];
    }
    discrete();
    for (i32 i = 1; i <= n; ++i) a[i] = Node(x[i], y[i], 0);
    for (i32 i = 1; i <= m; ++i) a[n + i] = Node(x[n + i], y[n + i], 1, i);
    t1.clear(), t2.clear();
    std::sort(a + 1, a + n + m + 1, [&](const Node &a, const Node &b)
      {
        if (a.x != b.x) return a.x < b.x;
        else return a.op < b.op;
      });
    for (i32 i = 1; i <= n + m; ++i) {
      if (a[i].op == 0) t1.add(a[i].y, - c[a[i].x] - c[a[i].y]), t2.add(a[i].y, - c[a[i].x] + c[a[i].y]);
      else {
        i64 r1 = t1.ask(a[i].y) + c[a[i].x] + c[a[i].y];
        i64 r2 = t2.ask(a[i].y) + c[a[i].x] - c[a[i].y];
        ans[a[i].id] = std::max({ans[a[i].id], r1, r2});
      }
    }
    t1.clear(), t2.clear();
    std::sort(a + 1, a + n + m + 1, [&](const Node &a, const Node &b)
      {
        if (a.x != b.x) return a.x > b.x;
        else return a.op < b.op;
      });
    for (i32 i = 1; i <= n + m; ++i) {
      if (a[i].op == 0) t1.add(a[i].y, + c[a[i].x] - c[a[i].y]), t2.add(a[i].y, + c[a[i].x] + c[a[i].y]);
      else {
        i64 r1 = t1.ask(a[i].y) - c[a[i].x] + c[a[i].y];
        i64 r2 = t2.ask(a[i].y) - c[a[i].x] - c[a[i].y];
        
        ans[a[i].id] = std::max({ans[a[i].id], r1, r2});
      }
    }
    i64 ret = -t1.s[0];
    for (i32 i = 1; i <= m; ++i) chkmin(ret, ans[i]);
    fprintf(fout, "%lld\n", ret);
    for (i32 i = 1; i <= m; ++i) if (ans[i] == ret) { fprintf(fout, "%d\n", i); break; }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1502::main(), 0; }