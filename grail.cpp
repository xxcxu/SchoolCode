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
namespace Solution_Of_grail {
  bool _1;
  static const i32 N = 1000005;
  static const i32 P = 998244353;
  i32 n;
  i32 a[N], d[N], st[N], top;
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("grail.in", "r");
    fout = fopen("grail.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) {
      while (top > 0 && a[i] > a[st[top]]) {
        d[i - st[top] + 1] = dec(d[i - st[top] + 1], a[st[top]] % P);
        d[i - st[top - 1] + 1] = inc(d[i - st[top - 1] + 1], a[st[top]] % P);
        --top;
      }
      d[1] = inc(d[1], a[i] % P);
      d[i - st[top] + 1] = dec(d[i - st[top] + 1], a[i] % P);
      st[++top] = i;
    }
    while (top > 0) {
      d[n - st[top] + 2] = dec(d[n - st[top] + 2], a[st[top]] % P);
      d[n - st[top - 1] + 2] = inc(d[n - st[top - 1] + 2], a[st[top]] % P);
      --top;
    }
    i32 s = 0, ans = 0;
    for (i32 i = 1; i <= n; ++i) {
      d[i] = inc(d[i], d[i - 1]);
      s = inc(s, d[i]);
      ans ^= s;
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_grail::main(), 0; }