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
namespace Solution_Of_necklace {
  bool _1;
  static const i32 N = 100005;
  i32 n;
  i32 a[N], prv[N], nxt[N], cnt[N];
  std::set<i32> s;
  bool _2;
  void del(i32 x) {
    i32 p = prv[x], q = nxt[x];
    prv[q] = p;
    nxt[p] = q;
    auto itp = s.find(p), itq = s.find(q);
    if (itp != s.end() && a[prv[p]] == a[nxt[p]]) s.erase(itp);
    if (itp == s.end() && a[prv[p]] != a[nxt[p]]) s.ep(p);
    if (itq != s.end() && a[prv[q]] == a[nxt[q]]) s.erase(itq);
    if (itq == s.end() && a[prv[q]] != a[nxt[q]]) s.ep(q);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("necklace.in", "r");
    fout = fopen("necklace.out", "w");
    fprintf(ferr, "%.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time = clock();
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) nxt[i] = (i == n ? 1 : i + 1);
    for (i32 i = 1; i <= n; ++i) prv[i] = (i == 1 ? n : i - 1);
    for (i32 i = 1; i <= n; ++i) if (a[nxt[i]] == a[i]) { fputs("no\n", fout); return void(); }
    for (i32 i = 1; i <= n; ++i) ++cnt[a[i]];
    if (!cnt[0] || !cnt[1] || !cnt[2]) { fputs("no\n", fout); return void(); }
    fputs("yes\n", fout);
    for (i32 i = 1; i <= n; ++i) if (a[prv[i]] != a[nxt[i]]) s.ep(i);
    for (i32 i = 1; i <= n - 3; ++i) {
      i32 now = *s.begin();
      if (cnt[a[now]] != 1) {
        fprintf(fout, "%d %d\n", prv[now], nxt[now]);
        --cnt[a[now]];
        s.erase(s.find(now));
        del(now);
      } else {
        fprintf(fout, "%d %d\n", prv[prv[now]], now);
        --cnt[a[prv[now]]];
        s.erase(s.find(prv[now]));
        del(prv[now]);
      }
    }
    i64 End_Time = clock();
    fprintf(ferr, "%lld ms time\n", End_Time - Start_Time);
    return void();
  }
}
signed main() { return Solution_Of_necklace::main(), 0; }