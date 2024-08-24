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
namespace Solution_Of_CF946G {
  bool _1;
  static const i32 N = 200005;
  i32 n, m, ans;
  i32 a[N], f[N], g[N];
  std::vector<i32> num;
  bool _2;
  struct TreeArray {
    i32 tr[N];
    void clear() {
      std::memset(tr, 0, sizeof tr);
      return void();
    }
    void add(i32 x, i32 v) {
      for (; x <= m; x += x & -x)
        chkmax(tr[x], v);
      return void();
    }
    i32 ask(i32 x) {
      i32 ans = 0;
      chkmin(x, m);
      for (; x > 0; x -= x & -x)
        chkmax(ans, tr[x]);
      return ans;
    }
  } t;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) num.eb(a[i] = read() - i);
    std::sort(all(num));
    num.erase(std::unique(all(num)), num.end());
    m = num.size();
    for (i32 i = 1; i <= n; ++i) a[i] = std::lower_bound(all(num), a[i]) - num.begin() + 1;
    t.clear();
    for (i32 i = 1; i <= n; ++i) {
      f[i] = t.ask(a[i]) + 1;
      t.add(a[i], f[i]);
      ans = std::max(ans, f[i] + 1);
    }
    t.clear();
    for (i32 i = n; i >= 1; --i) {
      g[i] = t.ask(m - a[i] + 1) + 1;
      t.add(m - a[i] + 1, g[i]);
      ans = std::max(ans, g[i] + 1);
    }
    t.clear();
    for (i32 i = 1; i < n; ++i) {
      i32 p = std::upper_bound(all(num), num[a[i + 1] - 1] + 1) - num.begin();
      ans = std::max(ans, t.ask(p) + g[i + 1] + 1);
      if (a[i] <= a[i + 1]) ans = std::max(ans, f[i] + g[i + 1]);
      t.add(a[i], f[i]);
    }
    fprintf(fout, "%d\n", std::max(n - ans, 0));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF946G::main(), 0; }