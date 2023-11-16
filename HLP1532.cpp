// 郑梓妍😭 钟晨瑶😭
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
namespace Solution_Of_HLP1532 {
  bool _1;
  static const i32 N = 1035;
  i32 n, m, q;
  i32 a[N][N], s[N][N], ans[N * N], count[N * N];
  i32 sx[N * N], sy[N * N], tx[N * N], ty[N * N];
  struct Node { i32 x, y; };
  struct qNode { i32 x, y, id; };
  std::vector<i32> val;
  std::vector<Node> pos[N * N];
  std::vector<qNode> qy[N * N];
  struct TreeArray {
    i32 s[N];
    void add(i32 x, i32 v) {
      for (; x <= m; x += x & -x)
        s[x] += v;
      return void();
    }
    void del(i32 x) {
      for (; x <= m; x += x & -x)
        s[x] = 0;
      return void();
    }
    i32 ask(i32 x) {
      i32 ans = 0;
      for (; x >= 1; x -= x & -x)
        ans += s[x];
      return ans;
    }
  } tr;
  bool _2;
  i32 query(i32 x, i32 y, i32 xx, i32 yy) {
    return s[xx][yy] - s[xx][y - 1] - s[x - 1][yy] + s[x - 1][y - 1];
  }
  void check(i32 x) {
    std::sort(all(qy[x]), [&](const qNode &a, const qNode &b) { return a.x < b.x; });
    for (i32 i = 0, j = 0; i < (i32)qy[x].size(); ++i) {
      while (j < (i32)pos[x].size() && pos[x][j].x <= qy[x][i].x) tr.add(pos[x][j].y, 1), ++j;
      if (qy[x][i].id < 0) count[-qy[x][i].id] -= tr.ask(qy[x][i].y);
      else count[qy[x][i].id] += tr.ask(qy[x][i].y);
    }
    for (i32 i = 0; i < (i32)pos[x].size(); ++i) tr.del(pos[x][i].y);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("hamo.in", "r");
    fout = fopen("hamo.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read(), m = read(), q = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j)
        a[i][j] = read();
    for (i32 i = 1; i <= n; ++i)
      for (i32 j = 1; j <= m; ++j)
        pos[a[i][j]].push_back({i, j});
    for (i32 i = 1; i <= q; ++i) sx[i] = read(), sy[i] = read(), tx[i] = read(), ty[i] = read();
    for (i32 d = 20; d >= 0; --d) {
      for (i32 i = 1; i <= n; ++i)
        for (i32 j = 1; j <= m; ++j)
          s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (a[i][j] >> d & 1);
      for (i32 i = 1; i <= q; ++i) {
        i32 tot = (tx[i] - sx[i] + 1) * (ty[i] - sy[i] + 1);
        i32 cnt = query(sx[i], sy[i], tx[i], ty[i]);
        if (cnt * 2 > tot) ans[i] |= (1 << d);
      }
    }
    for (i32 i = 1; i <= q; ++i) {
      val.eb(ans[i]);
      qy[ans[i]].push_back({tx[i], ty[i], i});
      qy[ans[i]].push_back({tx[i], sy[i] - 1, -i});
      qy[ans[i]].push_back({sx[i] - 1, ty[i], -i});
      qy[ans[i]].push_back({sx[i] - 1, sy[i] - 1, i});
    }
    std::sort(all(val));
    val.erase(std::unique(all(val)), val.end());
    for (i32 i : val) check(i);
    for (i32 i = 1; i <= q; ++i) {
      i32 tot = (tx[i] - sx[i] + 1) * (ty[i] - sy[i] + 1);
      if (count[i] * 2 > tot) fprintf(fout, "%d\n", ans[i]);
      else fputs("-1\n", fout);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1532::main(), 0; }