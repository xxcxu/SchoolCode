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
namespace Solution_Of_HLP1410 {
  bool _1;
  static const i32 N = 100005;
  static const i32 P = 1000000007;
  i32 n, m, k;
  i32 u[N], v[N], ind[N], cir[N], rnk[N], id[N], tot[N];
  std::vector<i32> e[N], g[N];
  bool _2;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  template<typename ...Args>
  i32 inc(i32 x, Args ...args) { return inc(x, inc(args...)); }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 fac[N], inv[N];
  void init(i32 n) {
    fac[0] = 1;
    for (i32 i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (i32 i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
  }
  i32 binom(i32 n, i32 m) {
    if (n < m || m < 0) return 0;
    return mul(fac[n], inv[m], inv[n - m]);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read(), k = read();
    for (i32 i = 1; i <= m; ++i) {
      u[i] = read(), v[i] = read();
      g[u[i]].eb(v[i]) ,g[v[i]].eb(u[i]);
    }
    i64 Start_Time_Without_Read = clock();
    i32 ans = 0;
    if (k == 1) {
      if (n >= 2) ans = mul(m, qpow(2, n - 2));
    }
    if (k == 2) {
      for (i32 i = 1; i <= m; ++i)
        ++ind[u[i]], ++ind[v[i]];
      for (i32 i = 1; i <= m; ++i) {
        if (n >= 2) ans = inc(ans, qpow(2, n - 2));
        if (n >= 3) ans = inc(ans, mul(qpow(2, n - 3), ind[u[i]] + ind[v[i]] - 2));
        if (n >= 4) ans = inc(ans, mul(qpow(2, n - 4), m - (ind[u[i]] + ind[v[i]] - 2) - 1));
      }
    }
    if (k == 3) {
      for (i32 i = 1; i <= m; ++i)
        ++ind[u[i]], ++ind[v[i]];
      bool flag = true;
      for (i32 i = 1; i <= m; ++i) flag &= (u[i] == 1 && v[i] == i + 1);
      init(N - 1);
      if (m == n - 1 && flag) {
        for (i32 i = 1; i <= n - 1; ++i)
          if (n >= 1) ans = inc(ans, mul(binom(n - 1, i), i, i, i));
      } else {
        i32 cnt = 0;
        i32 cnt_abc = 0;
        i32 cnt_abcd = 0;
        i32 cnt_abcd_ = 0;
        for (i32 i = 1; i <= n; ++i) rnk[i] = i; 
        std::sort(rnk + 1, rnk + n + 1, [&](i32 x, i32 y) { return ind[x] < ind[y] || (ind[x] == ind[y] && x < y); });
        for (i32 i = 1; i <= n; ++i) id[rnk[i]] = i;
        for (i32 i = 1; i <= m; ++i) {
          if (id[u[i]] > id[v[i]]) e[v[i]].eb(u[i]);
          else e[u[i]].eb(v[i]);
        }
        i32 all = 0;
        for (i32 i = 1; i <= n; ++i) {
          for (i32 j : e[i]) ++tot[j];
          for (i32 j : e[i]) for (i32 k : e[j]) all += tot[k];
          for (i32 j : e[i]) --tot[j];
        }
        // 2
        // (a, b)
        if (n >= 2) ans = inc(ans, mul(qpow(2, n - 2), m)); // 6
        cnt = inc(cnt, m);
        i32 part1 = ans;
        // 3
        // (a, b, c) cir
        if (n >= 3) ans = inc(ans, mul(qpow(2, n - 3), all, 6)); // 6
        cnt = inc(cnt, mul(all, 6));
        i32 part2 = dec(ans, part1);
        // (a, b, c)
        for (i32 i = 1; i <= m; ++i) {
          if (n >= 3) ans = inc(ans, mul(qpow(2, n - 3), ind[u[i]] + ind[v[i]] - 2, 3));
          cnt_abc = inc(cnt_abc, mul(ind[u[i]] + ind[v[i]] - 2, 3));
        }
        cnt = inc(cnt, cnt_abc);
        i32 part3 = dec(ans, inc(part1, part2));
        // 4
        // (a, b, c, d)
        for (i32 i = 1; i <= m; ++i) {
          if (n >= 4) ans = inc(ans, mul(qpow(2, n - 4), ind[u[i]] - 1, ind[v[i]] - 1, 6));
          cnt_abcd = inc(cnt_abcd, mul(ind[u[i]] - 1, ind[v[i]] - 1, 6));
        }
        if (n >= 4) ans = dec(ans, mul(qpow(2, n - 4), all, 3, 6));
        if (n >= 4) cnt_abcd = dec(cnt_abcd, mul(all, 3, 6));
        cnt = inc(cnt, cnt_abcd);
        i32 part4 = dec(ans, inc(part1, part2, part3));
        // (a, b) + (c, d)
        for (i32 i = 1; i <= m; ++i) {
          if (n >= 4) ans = inc(ans, mul(qpow(2, n - 4), m - ind[u[i]] - ind[v[i]] + 1, 3));
          cnt = inc(cnt, mul(m - ind[u[i]] - ind[v[i]] + 1, 3));
        }
        i32 part5 = dec(ans, inc(part1, part2, part3, part4));
        // (a, b) + (a, c) + (a, d)
        for (i32 i = 1; i <= m; ++i) {
          if (n >= 4) ans = inc(ans, mul(qpow(2, n - 4), binom(ind[u[i]] - 1, 2), 2));
          if (n >= 4) ans = inc(ans, mul(qpow(2, n - 4), binom(ind[v[i]] - 1, 2), 2));
          cnt = inc(cnt, mul(binom(ind[u[i]] - 1, 2), 2));
          cnt = inc(cnt, mul(binom(ind[v[i]] - 1, 2), 2));
          cnt_abcd_ = inc(cnt_abcd_, mul(binom(ind[u[i]] - 1, 2), 2));
          cnt_abcd_ = inc(cnt_abcd_, mul(binom(ind[v[i]] - 1, 2), 2));
        }
        i32 part6 = dec(ans, inc(part1, part2, part3, part4, part5));
        // 5
        // (a, b) + (c, d, e)
        for (i32 i = 1; i <= n; ++i) {
          i32 lst = 0;
          i32 _cnt = 0;
          for (i32 j : g[i]) {
            if (n >= 5) ans = inc(ans, mul(6, qpow(2, n - 5), dec(mul(m - ind[i] - ind[j] + 2, _cnt), lst)));
            cnt = inc(cnt, mul(dec(mul(m - ind[i] - ind[j] + 2, _cnt), lst), 6));
            lst = inc(lst, ind[j]);
            ++_cnt;
          }
        }
        if (n >= 5) ans = inc(ans, mul(all, 3, 6, qpow(2, n - 5)));
        cnt = inc(cnt, mul(all, 3, 6));
        // 6
        if (n >= 6) ans = inc(ans, mul(qpow(2, n - 6), dec(mul(m, m, m), cnt)));
      }
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1410::main(), 0; }
/*
6 7 3
1 4
1 3
1 2
2 3
4 3
3 5
4 6
*/
/*
5 6 3
1 4
1 3
1 2
2 3
4 3
3 5
*/
/*
4 4 3
1 2
1 3
2 3
3 4
*/
/*
3 3 3
1 2
2 3
3 1
*/