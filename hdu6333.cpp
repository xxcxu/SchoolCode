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
namespace Solution_Of_HDU6333 {
  bool _1;
  static const i32 N = 100005;
  static const i32 P = 1000000007;
  i32 n, t;
  i32 fac[N], ans[N], inv[N];
  struct Node {
    i32 l, r, id;
    Node() = default;
    Node(i32 l, i32 r, i32 id): l(l), r(r), id(id) {}
    bool operator <(const Node &a) const noexcept {
      if (this->l / t != a.l / t) return this->l < a.l;
      else return this->r < a.r;
    }
  } q[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
      i32 ans = 1;
      for (; y; y >>= 1, x = mul(x, x))
          if (y & 1) ans = mul(ans, x);
      return ans;
  }
  void init(i32 n) {
    fac[0] = 1;
    for (i32 i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (i32 i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
  }
  i32 binom(i32 n, i32 m) {
    if (n < m || m < 0) return 0;
    return mul(mul(fac[n], inv[m]), inv[n - m]);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    t = (i32)std::sqrt(n);
    init(N - 1);
    for (i32 i = 1; i <= n; ++i) q[i].l = read(), q[i].r = read(), q[i].id = i;
    std::sort(q + 1, q + n + 1);
    i32 L = 1, R = 0, res = 1;
    for (i32 i = 1; i <= n; ++i) {
      while (L < q[i].l) res = dec(mul(res, 2), binom(L, R)), ++L; // C(n, m) -> C(n + 1, m)
      while (L > q[i].l) res = mul(inc(res, binom(L - 1, R)), inv[2]), --L; // c(n, m) -> C(n - 1, m)
      while (R < q[i].r) res = inc(res, binom(L, R + 1)), ++R; // C(n, m) -> C(n, m + 1)
      while (R > q[i].r) res = dec(res, binom(L, R)), --R; // C(n, m) -> C(n, m - 1)
      ans[q[i].id] = res;
    }
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%d\n", ans[i]);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HDU6333::main(), 0; }
/*
S(n+1,m)=2S(n,m)-C(n,m)
S(n-1,m)=(S(n,m)+C(n-1,m))/2
S(n,m+1)=S(n,m)+C(n,m+1)
S(n,m-1)=S(n,m)-C(n,m)
*/