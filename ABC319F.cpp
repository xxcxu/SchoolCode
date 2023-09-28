#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using ui32 = uint32_t;
  using ui64 = uint64_t;
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  i32 read() {
    i32 t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
  class Iterator {
    public:
      Iterator(i32 _val = 0): _val(_val) {}
      bool operator !=(const Iterator &other) const { return this->_val != other._val; }
      i32 operator *() { return this->_val; }
      i32 operator ++() { return ++this->_val; }
    private:
      i32 _val;
  };
  class Range {
    public:
      Range(i32 _l = 0, i32 _r = 0): _begin(_l), _end(_r + 1) {}
      Iterator begin() { return Iterator(this->_begin); }
      Iterator end() { return Iterator(this->_end); }
    private:
      i32 _begin, _end;
  };
}
using namespace FileHeader;
namespace Solution_Of_ABC319F {
  bool _1;
#pragma endregion
  static constexpr i32 N = 505, M = 1u << 10;
  static constexpr i32 limitV = 1u << 30;
  
  i32 n;
  i32 dp[M];
  bool to[N][M];
  struct Vertex {
    i32 p, t, s, g;
    Vertex() = default;
    Vertex(i32 _p, i32 _t, i32 _s, i32 _g):
      p(_p), t(_t), s(_s), g(_g) {} 
  } a[N];
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    auto inc = [&](i32 x, i32 y)->i32 { return std::min(x + y, limitV); };
    auto mul = [&](i32 x, i32 y)->i32 { return std::min(1ll * x * y, 1ll * limitV); };
    n = read();
    std::vector<i32> spc;
    i32 max = 0;
    for (auto i = 2; i <= n; ++i) {
      a[i].p = read(), a[i].t = read(), a[i].s =  read(), a[i].g = read();
      max = std::max(max, a[i].s);
      if (a[i].t == 2) spc.eb(i);
    }
    i64 Start_Time_Without_Read = clock();
    i32 m = std::size(spc);
    to[1][0] = true;
    dp[0] = 1;
    for (auto S = 0; S < (1 << m); ++S) {
      while (true) {
        bool updated = false;
        for (auto i = 2; i <= n; ++i)
          if (a[i].t == 1 && to[a[i].p][S] && !to[i][S] && dp[S] >= a[i].s)
            to[i][S] = true, updated = true, dp[S] = inc(dp[S], a[i].g);
        if (updated == false) break;
      }
      for (auto i = 0; i < m; ++i)
        if ((~S >> i & 1) && to[a[spc[i]].p][S] && mul(dp[S], a[spc[i]].g) > dp[S | (1u << i)]) {
          i32 T = S | (1u << i);
          dp[T] = mul(dp[S], a[spc[i]].g);
          for (auto j = 1; j <= n; ++j) to[j][T] = to[j][S];
          to[spc[i]][T] = true;
        }
    }
    try {
      i32 R = 1u << m;
      for (auto i = 1; i <= n; ++i)
        if (!to[i][R - 1]) throw false;
      throw true;
    }
    catch (bool f) { fputs(f ? "Yes\n" : "No\n", fout); };
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_ABC319F::main(), 0; }