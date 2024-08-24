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
i64 read() {
  i64 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
namespace Solution_Of_gym104639F {
  bool _1;
  static const i32 N = 500005;
  i32 n, m, tot, cnt[N];
  i32 ch[N * 64][2];
  i64 size[N * 64 * 2];
  i64 ans, a[N], b[N];
  bool _2;
  i64 C2(i64 n) { if (n < 2) return 0; return n * (n - 1) / 2; }
  i64 C3(i64 n) { if (n < 3) return 0; return n * (n - 1) * (n - 2) / 6; }
  void insert(i64 x, i32 sz) {
    i32 p = 0;
    for (i32 i = 0; i <= 62; ++i) {
      i32 c = x >> i & 1;
      if (!ch[p][c]) ch[p][c] = ++tot;
      size[ch[p][c]] += sz;
      p = ch[p][c];
    }
    return void();
  }
  void search(i64 x, i32 sz) {
    i32 p = 0;
    for (i32 i = 0; i <= 62; ++i) {
      i32 c = x >> i & 1;
      if (i + 1 & 1) ans -= C2(sz) * size[ch[p][c ^ 1]];
      p = ch[p][c];
    }
    return void();
  }
  void solve() {
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = b[i] = read();
    std::sort(b + 1, b + n + 1);
    m = std::unique(b + 1, b + n + 1) - b - 1;
    for (i32 i = 1; i <= n; ++i) a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
    for (i32 i = 1; i <= m; ++i) cnt[i] = 0;
    for (i32 i = 1; i <= n; ++i) ++cnt[a[i]];
    ans = C3(n);
    for (i32 i = 1; i <= m; ++i) ans -= C3(cnt[i]);
    for (i32 i = 1; i <= m; ++i) insert(b[i], cnt[i]);
    for (i32 i = 1; i <= m; ++i) search(b[i], cnt[i]);
    for (i32 i = 0; i <= tot; ++i) ch[i][0] = ch[i][1] = size[i] = 0;
    tot = 0;
    fprintf(fout, "%lld\n", ans);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("answer.in", "r");
    fout = fopen("answer.out", "w");
    i32 t = read();
    while (t--) solve();
    return void();
  }
}
signed main() { return Solution_Of_gym104639F::main(), 0; }