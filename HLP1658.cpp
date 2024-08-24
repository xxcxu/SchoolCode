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
namespace Solution_Of_HLP1658 {
  bool _1;
  static const i32 N = 200005;
  i32 n, s[N], b[N];
  i64 ans;
  std::pair<i32, i32> a[N];
  std::vector<i32> vec[N];
  bool _2;
  i32 lowbit(i32 x) { return x & -x; }
  void add(i32 x, i32 v) {
    for (; x <= n; x += lowbit(x)) s[x] += v;
    return void();
  }
  i32 ask(i32 x) {
    i32 ans = 0;
    for (; x > 0; x -= lowbit(x)) ans += s[x];
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    fin = fopen("time.in", "r");
    fout = fopen("time.out", "w");
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i].first = read();
    for (i32 i = 1; i <= n; ++i) vec[a[i].first].eb(i);
    for (i32 i = 1; i <= n; ++i) a[i].second = i;
    std::priority_queue<i32> q;
    for (i32 i = n; i >= 1; --i) {
      for (auto it : vec[i]) q.ep(it);
      if (q.size()) { b[i] = q.top(); q.pop(); }
      else { return fputs("-1\n", fout), void(); }
    }
    for (i32 i = n; i >= 1; --i) ans += ask(b[i]), add(b[i], 1);
    fprintf(fout, "%lld\n", ans); 
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_HLP1658::main(), 0; }