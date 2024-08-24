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
namespace Solution_Of_HLP1614 {
  bool _1;
  static const i32 P = 998244353;
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
  i64 n;
  i32 a, b;
  bool _2;
  struct Matrix {
    i32 n, m;
    i32 a[2][2];
    Matrix(i32 n = 0, i32 m = 0, i32 p = 0): n(n), m(m) {
      for (i32 i = 0; i < n; ++i)
        for (i32 j = 0; j < m; ++j) a[i][j] = 0;
      if (p) for (i32 i = 0; i < n; ++i) a[i][i] = 1;
    }
    friend Matrix operator * (const Matrix &a, const Matrix &b) {
      Matrix ans = Matrix(a.n, b.m);
      for (i32 i = 0; i < a.n; ++i)
        for (i32 j = 0; j < b.m; ++j)
          for (i32 k = 0; k < a.m; ++k)
            ans.a[i][j] = inc(ans.a[i][j], mul(a.a[i][k], b.a[k][j]));
      return ans;
    }
    friend Matrix operator ^ (Matrix a, i64 k) {
      if (k == 0) return Matrix(a.n, a.m, 1);
      Matrix ans = a;
      for (k = k - 1; k; k >>= 1, a = a * a) if (k & 1) ans = ans * a;
      return ans;
    }
  } f, base;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("poly.in", "r");
    fout = fopen("poly.out", "w");
    a = read(), b = read(), n = read();
    f = Matrix(1, 2);
    base = Matrix(2, 2);
    f.a[0][1] = a;
    f.a[0][0] = dec(mul(a, a), mul(b, 2));
    base.a[0][0] = a; base.a[0][1] = 1;
    base.a[1][0] = dec(0, b); base.a[1][1] = 0;
    if (n <= 2) fprintf(fout, "%d\n", f.a[0][n - 1]);
    else {
      f = f * (base ^ (n - 2));
      fprintf(fout, "%d\n", f.a[0][0]);
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1614::main(), 0; }