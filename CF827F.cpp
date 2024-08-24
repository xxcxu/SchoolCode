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
namespace Solution_Of_CF827F {
  bool _1;
  static const i32 N = 500005;
  i32 n, m;
  struct Node {
    i32 v, l, r;
    Node() = default;
    Node(i32 v, i32 l, i32 r):
      v(v), l(l), r(r) {}
    const bool operator <(const Node &a) const noexcept { return this->l > a.l; }
  };
  bool flag;
  std::vector<Node> e[N * 2];
  std::priority_queue<Node> q;
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read(), m = read();
    auto add = [&](i32 x, i32 y, i32 l, i32 r) { if (l <= r) e[x].eb(y, l, r); return void(); };
    for (i32 i = 1; i <= m; ++i) {
      static i32 u, v, l, r;
      u = read(), v = read(), l = read(), r = read();
      i32 p = l & 1, q = r & 1;
      add(u, v + n, l + p, r - !q);
      add(u + n, v, l + !p, r - q);
      add(v, u + n, l + p, r - !q);
      add(v + n, u, l + !p, r - q);
    }
    for (i32 i = 1; i <= n * 2; ++i) std::sort(all(e[i]));
    q.ep(1, 0 ,0);
    while (q.size()) {
      auto [x, l, r] = q.top(); q.pop();
      if (x == n || x == n + n) {
        fprintf(fout, "%d\n", l);
        flag = true;
        break;
      }
      while (e[x].size() && e[x].back().l <= r) {
        if (e[x].back().r >= l) {
          if (e[x].back().l <= l) e[x].back().l = l;
          ++e[x].back().l, ++e[x].back().r;
          q.ep(e[x].back());
        }
        e[x].pop_back();
      }
    }
    if (!flag) fputs("-1\n", fout);
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_CF827F::main(), 0; }