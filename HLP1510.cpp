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
namespace Solution_Of_HLP1510 {
  bool _1;
  static const i32 N = 10000005;
  static const i32 P = 1000000007;
  i32 n, k, ans;
  i32 id[N], max[N];
  i64 pre[N], suf[N], val[N], dp[N], head, tail, pos;
  i32 a[N], fpow[N];  
  bool _2;
  i32 inc(i32 x, i32 y) { return (1LL * x + y) % P; }
  i32 dec(i32 x, i32 y) { return (1LL * x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  void rebuild() {
    pos = (head + tail) >> 1;
    pre[pos] = suf[pos] = val[pos];
    for (i32 i = pos - 1; i >= head; --i) pre[i] = std::min(pre[i + 1], val[i]);
    for (i32 i = pos + 1; i <= tail; ++i) suf[i] = std::min(suf[i - 1], val[i]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("knight.in", "r");
    fout = fopen("knight.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), k = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    std::memset(dp, 0x3f, sizeof dp);
    fpow[0] = 1;
    for (i32 i = 1; i <= n; ++i) fpow[i] = mul(fpow[i - 1], 23);
    head = 1, tail = 0, pos = 0;
    dp[0] = 0;
    for (i32 i = 1; i <= n; ++i) {
      if (head <= tail && i > k) {
        if (id[head] == i - k) ++head;
        else pre[head] = std::min(pre[head + 1], val[head] = dp[i - k] + max[head]);
      }
      while (head <= tail && a[i] >= max[tail]) --tail;
      ++tail;
      id[tail] = i, max[tail] = a[i];
      val[tail] = (head < tail ? dp[id[tail - 1]] : dp[std::max(i - k, 0)]) + max[tail];
      suf[tail] = std::min(suf[tail - 1], val[tail]);
      if (!(head < pos && pos < tail)) rebuild();
      dp[i] = std::min(pre[head], suf[tail]);
      ans = inc(ans, mul(fpow[n - i], dp[i] % P));
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1510::main(), 0; }