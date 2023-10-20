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
namespace Solution_Of_CF1305G {
  bool _1;
  static const i32 N = (1 << 18) + 5;
  i32 n; i64 ans;
  i32 a[N], fa[N], cnt[N], size[N];
  bool _2;
  i32 find(i32 x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
  void merge(i32 x, i32 y, i32 z) {
    if (!cnt[x] || !cnt[y]) return void();
    x = find(x), y = find(y);
    if (x == y) return void();
    if (size[x] > size[y]) std::swap(x, y);
    ans += 1ll * z * (cnt[x] + cnt[y] - 1);
    fa[x] = y;
    cnt[y] = 1;
    size[y] += size[x];
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    ++cnt[0];
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) ans -= a[i];
    for (i32 i = 1; i <= n; ++i) ++cnt[a[i]];
    i32 m = 1;
    i32 max = *std::max_element(a + 1, a + n + 1);
    while (m <= max) m <<= 1;
    for (i32 i = 0; i <= m; ++i) fa[i] = i, size[i] = 1;
    for (i32 S = m; S >= 0; --S) {
      for (i32 T = S; T; T = (T - 1) & S)
        merge(T, S ^ T, S);
      merge(S, 0, S);
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1305G::main(), 0; }