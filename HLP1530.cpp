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
namespace Solution_Of_HLP1530 {
  bool _1;
  static const i32 N = 500005;
  i32 n;
  struct Node { i32 a, b; } a[N];
  bool _2;
  struct compare {
    bool operator ()(i32 &x, i32 &y) { return a[x].a < a[y].a; }
  };
  std::priority_queue<i32, std::vector<i32>, compare> q;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("ball.in", "r");
    fout = fopen("ball.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i].a = read();
    for (i32 i = 1; i <= n; ++i) a[i].b = read();
    std::sort(a + 1, a + n + 1, [&](const Node &a, const Node &b) { return a.a + a.b < b.a + b.b; });
    i32 ans = 0; i64 now = 0;
    for (i32 i = 1; i <= n; ++i){
      if (a[i].b >= now) now += a[i].a, q.ep(i);
      else if (a[q.top()].a > a[i].a) now += a[i].a - a[q.top()].a, q.pop(), q.push(i);
      ans = std::max(ans, (i32)q.size());
    }
    fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1530::main(), 0; }