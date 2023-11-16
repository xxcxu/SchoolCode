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
template <typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); }
template <typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; }
#pragma endregion
namespace Solution_Of_HLP1504 {
  bool _1;
  static const i32 N = 5000005;
  i32 n;
  char s[N], t[N], ans[N];
  i32 len[N], res[N];
  bool _2;
  std::vector<std::pair<i32, i32>> vec;
  bool check(i32 k) {
    std::memcpy(t + 1, s + 1, n * sizeof(char));
    for (auto [l, r] : vec)
      for (i32 j = l - k; j < l; ++j) t[j] = '1';
    if (t[1] == '0' && t[2] == '1') return false;
    if (t[n - k] == '0' && t[n - k - 1] == '1') return false;
    for (i32 i = 1; i <= n - k; ++i)
      if (t[i] == '0') {
        i32 r = i;
        while (r <= n - k && t[r + 1] == '0') ++r;
        --r;
        if (i != 1) ++i;
        if (i > r) continue;
        while (r - i + 1 >= 3)
          t[i] = '1', i += 2;
        if (r - i + 1 == 2) {
          if (k == 1) return false;
          t[i] = t[i + 1] = '1';
        } else t[i] = '1';
        i = r + 2; 
      }
    for (i32 i = 1; i < n - k; ++i) if (t[i] == '0' && t[i + 1] == '0') return false;
    return true;
  }
  void print(char *s) {
    fputs("Yes\n", fout);
    for (i32 i = 1; i <= n; ++i)
      fputc(s[i] == '1' ? 'B' : 'R', fout);
    fputs("\n", fout);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("soccer.in", "r");
    fout = fopen("soccer.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i64 Start_Time_Without_Read = clock();
    n = read();
    fscanf(fin, "%s", s + 1);
    for (i32 i = 1; i <= n; ++i) {
      if (s[i] == '0') continue;
      i32 r = i;
      while (r < n && s[r + 1] == '1') ++r;
      vec.eb(i, r);
      i = r + 1;
    }
    if (!vec.size()) print(s);
    else {
      i32 min = n + 1, max = 0;
      for (i32 i = 1; i < std::size(vec); ++i) {
        i32 d = vec[i].first - vec[i - 1].second - 2;
        chkmin(min, d), chkmax(max, d);
      }
      chkmin(min, vec[0].first - 1);
      chkmax(max, vec[0].first - 1);
      chkmin(min, n - vec.rbegin()->second);
      chkmax(max, n - vec.rbegin()->second);
      if (max == 0) print(s);
      else if (min >= 1 && check(1)) print(t);
      else if (min >= 2 && check(2)) print(t); 
      else if (min >= 3 && check(3)) print(t); 
      else fputs("No\n", fout);
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1504::main(), 0; }