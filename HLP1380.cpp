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
namespace Solution_Of_HLP1380 {
  bool _1;
  static const i32 N = 5005;
  static const i32 inf32 = 0x3f3f3f3f;
  i32 n, fa[N];
  struct line {
    i32 l, r;
    line() = default;
    line(i32 l, i32 r): l(l), r(r) {}
  } a[N];
  bool _2;
  std::vector<i32> son[N];
  void _build() {
    std::stack<i32> st;
    for (i32 i = 1; i <= n; ++i) {
      while (st.size() && a[i].r > a[st.top()].r) st.pop();
      if (st.size()) son[st.top()].eb(i), fa[i] = st.top();
      st.ep(i);
    }
    return void();
  }
  #define for_statue(a, b) for (i32 a = 0; a < 2; ++a) for (i32 b = 0; b < 2; ++b)
  i32 L[N], R[N], size[N], f[N][N][2][2], g[N][2][2];
  bool leaf(i32 x) { return (i32)son[x].size() == 0; }
  void dfs(i32 x, i32 fas) {
    if (leaf(x)) {
      L[x] = a[x].l, R[x] = a[x].r;
      size[x] = 2;
      f[x][1][0][0] = R[x] - L[x];
      return void();
    }
    L[x] = inf32, R[x] = -inf32;
    size[x] = 1;
    i32 lst = 0;
    std::memset(f[x], 0xc0, sizeof f[x]);
    for (i32 y : son[x]) {
      dfs(y, fas + 1);
      i32 new_size = std::min(size[x] + size[y], fas);
      L[x] = std::min(L[x], L[y]);
      R[x] = std::max(R[x], R[y]);
      for (i32 i = 0; i <= new_size; ++i) for_statue(a, b) g[i][a][b] = -inf32;
      if (!lst) {
        for (i32 i = 1; i <= new_size; ++i)
          for_statue(aa, bb) {
            chkmax(g[i - 1][aa][bb], f[y][i][aa][bb]);
            if (!aa) chkmax(g[i][1][bb], f[y][i][0][bb] + L[y] - a[x].l);
          }
      } else {
        for (i32 i = 0; i <= size[x]; ++i)
          for (i32 j = 1; j <= fas - i && j <= size[y]; ++j)
            for_statue(a, b) for_statue(aa, bb) {
              chkmax(g[i + j - 1][a][bb], f[x][i][a][b] + f[y][j][aa][bb]);
              if (!b && !aa) chkmax(g[i + j][a][bb], f[x][i][a][0] + f[y][j][0][bb] + L[y] - R[lst]);
            }
      }
      size[x] = new_size;
      for (i32 i = 0; i < size[x]; ++i) for_statue(a, b)
          if (lst) chkmax(g[i + 1][a][b], g[i][a][b]);
      for (i32 i = 0; i <= size[x]; ++i) for_statue(a, b)
          chkmax(f[x][i][a][b], g[i][a][b]);
      lst = y;
    }
    for (i32 i = 0; i < size[x]; ++i) for_statue(aa, bb) chkmax(f[x][i + 1][aa][1], f[x][i][aa][0] + a[x].r - R[x]);
    for (i32 i = 0; i < size[x]; ++i) for_statue(a, b) chkmax(f[x][i + 1][a][b], f[x][i][a][b]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i)
      a[i].l = read(), a[i].r = read();
    i64 Start_Time_Without_Read = clock();
    std::sort(a + 1, a + n + 1, [&](const line &a, const line &b) { return a.l < b.l || (a.l == b.l && a.r < b.r); });
    _build();
    i32 ans = 0;
    for (i32 i = 1; i <= n; ++i) 
      if (!fa[i]) {
        dfs(i, 2);
        i32 ret = 0;
        for_statue(a, b) chkmax(ret, f[i][1][a][b]);
        ans += ret;
      }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1380::main(), 0; }