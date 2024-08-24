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
namespace Solution_Of_C24126 {
  bool _1;
  static const i32 N = 1000005, M = 105;
  static const i32 P = 1000000007;
  static const i32 dx[] = {0, 0, -1, 1};
  static const i32 dy[] = {1, -1, 0, 0};
  i32 H, W, n, mx, my;
  i32 ax[N], ay[N], cntx[N], cnty[N];
  i32 res, ans, sum[N];
  bool vis[M][M], vis2[M][M];
  struct Node {
    i32 x, y;
    Node() = default;
    Node(i32 x, i32 y): x(x), y(y) {}
  } a[N];
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
  i32 inv(i32 x) { return qpow(x, P - 2); }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    fin = fopen("dist.in", "r");
    fout = fopen("dist.out", "w");
    auto solve = [&]() {
      H = read(), W = read(), n = read(), mx = 0, my = 0;
      std::memset(cntx, 0, sizeof cntx);
      std::memset(cnty, 0, sizeof cnty);
      for (i32 i = 1; i <= n; ++i) a[i].x = read(), a[i].y = read();
      ans = 0;
      for (i32 i = 1; i <= H; ++i) sum[i] = 0;
      for (i32 i = 1; i <= n; ++i) sum[a[i].x] = dec(sum[a[i].x], 1);
      for (i32 i = 1; i <= H; ++i) {
        sum[i] = inc(sum[i], inc(sum[i - 1], W));
        if (i == 1 || (i > 1 && dec(sum[i], sum[i - 1]) == W && dec(sum[i - 1], sum[i - 2]) != W))
          ax[n + (++mx)] = i;
        if (i > 1 && dec(sum[i], sum[i - 1]) == W && dec(sum[i - 1], sum[i - 2]) == W) {
          ++cntx[ax[n + mx]];
          ans = inc(ans, mul(sum[i - 1], dec(dec(mul(H, W), n), sum[i - 1])));
        }
      }
      for (i32 i = 1; i <= W; ++i) sum[i] = 0;
      for (i32 i = 1; i <= n; ++i) sum[a[i].y] = dec(sum[a[i].y], 1);
      for (i32 i = 1; i <= W; ++i) { 
        sum[i] = inc(sum[i], inc(sum[i - 1], H));
        if (i == 1 || (i > 1 && dec(sum[i], sum[i - 1]) == H && dec(sum[i - 1], sum[i - 2]) != H))
          ay[n + (++my)] = i;
        if (i > 1 && dec(sum[i], sum[i - 1]) == H && dec(sum[i - 1], sum[i - 2]) == H) {
          ++cnty[ay[n + my]];
          ans = inc(ans, mul(sum[i - 1], dec(dec(mul(H, W), n), sum[i - 1])));
        }
      }
      res = 0;
      {
        i32 l;
        for (i32 i = 1; i <= n; ++i) ax[i] = a[i].x;
        std::sort(ax + 1, ax + n + mx + 1);
        l = std::unique(ax + 1, ax + n + mx + 1) - ax - 1;
        H = l;
        for (i32 i = 1; i <= n; ++i) a[i].x = std::lower_bound(ax + 1, ax + l + 1, a[i].x) - ax;
        for (i32 i = 1; i <= n; ++i) ay[i] = a[i].y;
        std::sort(ay + 1, ay + n + my + 1);
        l = std::unique(ay + 1, ay + n + my + 1) - ay - 1;
        W = l;
        for (i32 i = 1; i <= n; ++i) a[i].y = std::lower_bound(ay + 1, ay + l + 1, a[i].y) - ay;
      }
      std::memset(vis, 0, sizeof vis);
      for (i32 i = 1; i <= n; ++i) vis[a[i].x][a[i].y] = true;
      for (i32 i = 1; i <= H; ++i)
        for (i32 j = 1; j <= W; ++j) {
          if (!vis[i][j]) {
            std::memset(vis2, 0, sizeof vis2);
            std::queue<std::array<i32, 3>> q;
            q.push({i, j, 0});
            while (q.size()) {
              auto [x, y, D] = q.front();
              q.pop();
              if (vis2[x][y]) continue;
              vis2[x][y] = true;
              res = inc(res, mul(mul(mul(cntx[ax[i]] + 1, cnty[ay[j]] + 1), mul(cntx[ax[x]] + 1, cnty[ay[y]] + 1)), D));
              for (i32 d = 0; d < 4; ++d) {
                i32 xx = x + dx[d], yy = y + dy[d];
                if (xx < 1 || xx > H || yy < 1 || yy > W) continue;
                if (vis[xx][yy] || vis2[xx][yy]) continue;
                q.push({xx, yy, D + 1});
              }
            }
          }
        }
      fprintf(fout, "%d\n", inc(ans, mul(res, inv(2))));
    };
    i32 t = read();
    while (t--) solve();
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_C24126::main(), 0; }