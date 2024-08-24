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
namespace Solution_Of_fib {
  bool _1;
  static const i32 P = 10000;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
      i32 ans = 1;
      for (; y; y >>= 1, x = mul(x, x))
          if (y & 1) ans = mul(ans, x);
      return ans;
  }
  i32 inv(i32 x) { return qpow(x, P - 2); }
  i32 n;
  class Matrix {
      private: i32 n, m;
      public: std::vector<std::vector<i32>> a;
      public: Matrix(i32 n = 0, i32 m = 0, i32 p = 0): n(n), m(m) {
          a.resize(n, std::vector<i32>(m, 0));
          if (p) for (i32 i = 0; i < n; ++i) a[i][i] = 1;
      }
      public: std::vector<i32>& operator [] (i32 x) & {return a[x];}
      public: const std::vector<i32>& operator[](i32 x) const& {return a[x];}
      public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
          Matrix ans = Matrix(a.n, b.m);
          for (i32 i = 0; i < a.n; ++i)
              for (i32 j = 0; j < b.m; ++j)
                  for (i32 k = 0; k < a.m; ++k)
                      ans.a[i][j] = inc(ans.a[i][j], mul(a.a[i][k], b.a[k][j]));
          return ans;
      }
      public: friend Matrix operator ^ (Matrix a, i32 k) {
          if (k == 0) return Matrix(a.n, a.m, 1);
          Matrix ans = a;
          for (k = k - 1; k; k >>= 1, a = a * a) if (k & 1) ans = ans * a;
          return ans;
      }
  } f, base;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fin = fopen("fib.in", "r");
    fout = fopen("fib.out", "w");
    i64 Start_Time = clock();
    while (true) {
      n = read();
      if (n == -1) break;
      f = Matrix(1, 2);
      f[0][0] = 0, f[0][1] = 1;
      base = Matrix(2, 2);
      base[0][0] = 0, base[0][1] = 1;
      base[1][0] = 1, base[1][1] = 1;
      if (n) f = f * (base ^ (n - 1));
      if (n == 0) fprintf(fout, "%d\n", 0);
      else fprintf(fout, "%d\n", f[0][1]);
    }
    
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_fib::main(), 0; }