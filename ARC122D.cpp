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
namespace Solution_Of_ARC122D {
  bool _1;
  static constexpr i32 N = 200005;
  i32 n;
  i32 a[N * 2];
  bool _2;
  class Trie {
    private:
    i32 ch[N * 31 * 2][2];
    i32 tot = 0;
    public:
    void clear() {
      for (i32 i = 0; i <= tot; ++i)
        ch[i][0] = ch[i][1] = 0;
      tot = 0;
      return void();
    }
    void insert(i32 x) {
      i32 p = 0;
      for (i32 i = 30; i >= 0; --i) {
        i32 c = x >> i & 1;
        if (!ch[p][c]) ch[p][c] = ++tot;
        p = ch[p][c];
      }
      return void();
    }
    i32 query(i32 x) {
      i32 ans = 0, p = 0;
      for (i32 i = 30; i >= 0; --i) {
        i32 c = x >> i & 1;
        if (ch[p][c]) p = ch[p][c];
        else ans |= 1 << i, p = ch[p][c ^ 1];
      }
      return ans;
    }
  } t;
  i32 solve(const std::vector<i32> &v, i32 d) {
    if (v.empty()) return 0;
    if (d == -1) return 0;
    std::vector<i32> vec[2];
    for (auto it : v) vec[it >> d & 1].eb(it);
    if ((vec[0].size()) % 2 == 0)
      return std::max(solve(vec[0], d - 1), solve(vec[1], d - 1));
    t.clear();
    i32 ans = 0x7fffffff;
    for (auto it : vec[0]) t.insert(it);
    for (auto it : vec[1]) ans = std::min(ans, t.query(it));
    return ans;
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    std::vector<i32> v;
    for (i32 i = 1; i <= n * 2; ++i) a[i] = read(), v.eb(a[i]);
    fprintf(fout, "%d\n", solve(v, 30));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_ARC122D::main(), 0; }