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
namespace Solution_Of_HLP1544 {
  static const i32 N = 100005;
  i32 n;
  i32 a[N];
  std::vector<std::pair<i32, i64>> vec;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("mod.in", "r");
    fout = fopen("mod.out", "w");
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    // 2n+1
    i64 s = 0;
    vec.eb(2, n); 
    for (i32 i = n; i >= 1; --i) {
      vec.eb(1, a[i] - a[i - 1] + 100000);
      s += a[i] - a[i - 1] + 100000;
      if (i != 1) vec.eb(2, s + (i - 1));
    }
    vec.eb(2, 100000);
    /*
    3n+1
    for (i32 i = 1; i <= n; ++i) vec.eb(1, 100000), vec.eb(2, 1LL * i * 100000 + (n - i + 1));
    vec.eb(1, 2 * 100000);
    for (i32 i = 1; i <= n; ++i) b[i] = 1LL * (i - 1) * 100000 + 200000;
    for (i32 i = n; i >= 1; --i) vec.eb(2, b[i] - a[i]);
    */
    fprintf(fout, "%d\n", (i32)vec.size());
    for (auto &[fi, se] : vec) fprintf(fout, "%d %lld\n", fi, se);
    return void();
  }
}
signed main() { return Solution_Of_HLP1544::main(), 0; }