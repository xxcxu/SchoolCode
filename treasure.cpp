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
namespace Solution_Of_treasure {
  bool _1;
  static const i32 N = 405, S = 1 << 16;
  static const i32 inf32 = 0x3f3f3f3f;
  i32 n, m, K, q;
  i32 ban[16], key[16], open[N];
  bool isban[N], iskey[N];
  i32 dis1[N][N], dis2[S][16][16], dis3[S][32][32], dis4[N][N], ans[N][N];
  bool _2;
  i32 get(i32 x) { return std::__lg(x); }
  bool check(i32 x, i32 S) {
    return (open[x] & S) == open[x];
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    /*
    dis1[i][j] i->j no ban
    dis2[S][i][j] keyset S ban[i]->ban[j]
    dis3[i][j] spc[i]->spc[j]
    dis4[S][i][j] keyset S key[i]->ban[j]
    */
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    std::memset(dis1, 0x3f, sizeof dis1);
    std::memset(dis2, 0x3f, sizeof dis2);
    std::memset(dis3, 0x3f, sizeof dis3);
    std::memset(dis4, 0x3f, sizeof dis4);
    std::memset(ans, 0x3f, sizeof ans);
    n = read(), m = read(), K = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) dis1[i][i] = 0;
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, w;
      u = read(), v = read(), w = read();
      dis1[u][v] = std::min(dis1[u][v], w);
      dis1[v][u] = std::min(dis1[v][u], w);
    }
    for (i32 i = 0; i < K; ++i) {
      static i32 u, v;
      u = read(), v = read();
      isban[u] = true, iskey[v] = true;
      ban[i] = u, key[i] = v;
      open[u] |= (1 << i);
    }
    for (i32 k = 1; k <= n; ++k)
      if (!isban[k])
        for (i32 i = 1; i <= n; ++i)
          for (i32 j = 1; j <= n; ++j)
            chkmin(dis1[i][j], dis1[i][k] + dis1[k][j]);
    auto pos=[&](const int&x){return x<K?ban[x]:key[x-K];};
    for (i32 i = 0; i < K * 2; ++i)
      for (i32 j = 0; j < K * 2; ++j)
        dis3[0][i][j] = dis1[pos(i)][pos(j)];
    for (i32 S = 1; S < (1 << K); ++S)
      for (i32 k = 0; k < K; ++k)
        if (S >> k & 1) {
          std::memcpy(dis3[S], dis3[S ^ (1 << k)], sizeof dis3[S ^ (1 << k)]);
          if (check(ban[k], S))
            for (i32 i = 0; i < K * 2; ++i)
              if (dis3[S][i][k] != inf32)
                for (i32 j = 0; j < K * 2; ++j)
                  chkmin(dis3[S][i][j], dis3[S][i][k] + dis3[S][k][j]);
        }
    for (i32 i = 0; i < K; ++i)
      if (check(key[i], 0))
        dis2[1 << i][i][i] = 0;
    for (i32 S = 1; S < (1 << K); ++S) {
      std::vector<i32> vec[2];
      for (i32 i = 0; i < K; ++i)
        vec[S >> i & 1].eb(i);
      for (const auto &i : vec[1])
        for (const auto &k : vec[1])
          if (dis2[S][i][k] != inf32)
            for (const auto &j : vec[0])
              if (check(key[j], S))
                chkmin(dis2[S ^ (1 << j)][i][j], dis2[S][i][k] + dis3[S][k + K][j + K]);
    }
    for (i32 i = 0; i < K; ++i)
      for (i32 S = 0; S < (1 << K); ++S)
        if (S >> i & 1)
          for (i32 j = 0; j < K; ++j)
            if (check(ban[j], S))
              for (i32 T = S; T; T ^= (T & -T))
                chkmin(dis4[i][j], dis2[S][i][get(T & -T)] + dis3[S][get(T & -T) + K][j]); 
    for (i32 i = 1; i <= n; ++i)
      if (!isban[i])
        for (i32 j = 1; j <= n; ++j) {
          if (!isban[j]) ans[i][j] = dis1[i][j];
          for (i32 x = 0; x < K; ++x)
            if (check(key[x], 0))
              for (i32 y = 0; y < K; ++y)
                if (ban[y] == j || !isban[j])
                  chkmin(ans[i][j], dis1[i][key[x]] + dis1[j][ban[y]] + dis4[x][y]);
        }
    q = read();
    while (q--) {
      static i32 u, v;
      u = read(), v = read();
      fprintf(fout, "%d\n", ans[u][v] >= 0x3f3f3f3f ? -1 : ans[u][v]);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_treasure::main(), 0; }