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
  namespace Solution_Of_UOJ21 {
    bool _1;
    static const i32 N = 1000005;
    i32 n;
    i64 ans, s;
    i32 a[N], cnt[N];
    bool _2;
    void main() {
      fin = stdin, fout = stdout, ferr = stderr;
      fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
      i64 Start_Time = clock();
      n = read();
      for (i32 i = 1; i <= n; ++i) a[i] = read(), s += a[i];
      for (i32 i = 1; i <= n; ++i) ++cnt[a[i]];
      for (i32 i = 1; i < N; ++i) cnt[i] += cnt[i - 1];
      ans = 1000000000000000000;
      for (i32 i = 1; i < N; ++i) {
        i64 res = 0;
        for (i32 j = 0; i * j < N; ++j) {
          i32 l = i * j, r = std::min(i * (j + 1) - 1, N - 1);
          i32 t = cnt[r] - cnt[l - 1];
          res += 1ll * j * (i - 1) * t;      
        }
        ans = std::min(ans, s - res);
      }
      fprintf(fout, "%lld\n", ans);
      i64 End_Time = clock();
      fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
      return void();
    }
  }
  signed main() { return Solution_Of_UOJ21::main(), 0; }