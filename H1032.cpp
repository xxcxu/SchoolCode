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
namespace Solution_Of_H1032 {
  bool _1;
  static const i32 N = 200005;
  i32 n, m;
  i32 a[N], b[N], cnt[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    m = std::unique(b + 1, b + n + 1) - b - 1;
    if (m == 1) {
      for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d ", i);
    } else {
      for (i32 i = 1; i <= n; ++i) {
        a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
        ++cnt[a[i]];
      }
      i32 cnt1 = 0, cnt2 = cnt[m];
      for (i32 i = 1; i < m; ++i) if (b[m] % b[i] != 0) cnt1 += cnt[i];
      for (i32 i = 1; i < m - 1; ++i) if (b[m - 1] % b[i] != 0) cnt2 += cnt[i];
      bool flag = false;
      for (i32 i = 1; i <= n; ++i) {
        if (a[i] == m && cnt1 < 2) fprintf(fout, "%d ", i), flag = true;
        if (a[i] == m - 1 && cnt2 < 2) fprintf(fout, "%d ", i), flag = true;
      }
      if (!flag) fputs("NO\n", fout);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_H1032::main(), 0; }