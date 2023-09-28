#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int64_t;
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
namespace Solution_Of_triple {
  bool _1;
#pragma endregion
  static const i32 inf64 = 0x3f3f3f3f3f3f3f3f;
  i32 p, q, r, a, b, c;
  int ans;
  bool _2;
  i32 calc(i32 p, i32 q, i32 a, i32 b) {
    if (p == q) return inf64;
    i32 t = (b * p - a * q) / (p - q);
    if (t * (p - q) == b * p - a * q) return t;
    return inf64;
  }
  i32 calc2(i32 p, i32 q, i32 a, i32 b) {
    if (a == b) return inf64;
    i32 t = (b * p - a * q) / (a - b);
    if (t * (a - b) == b * p - a * q) return t;
    return inf64;
  }
  void solve1(i32 p, i32 q, i32 r, i32 a, i32 b, i32 c, i32 x) {
    if (x != inf64)
      if (p != 0 || q != 0)
        if (i32 t = p ? (a - x) / p : (b - x) / q; t * p + x == a && t * q + x == b) {
          if (x != 0) {
            if (t != 1) {
              ans = std::min(ans, 3);
              if (t * r + x == c || t * r == c || r + x == c || r == c) ans = std::min(ans, 2);
            }
          }
          else
            if (t != 1) {
              ans = std::min(ans, 2);
              if (t * r == c || r == c) ans = std::min(ans, 1);
            }
        }
    return void();
  }
  void solve2(i32 p, i32 q, i32 r, i32 a, i32 b, i32 c, i32 x) {
    if (x != inf64)
      if (p + x != 0 || q + x != 0)
        if (i32 t = (p + x) ? a / (p + x) : b / (q + x); (p + x) * t == a && (q + x) * t == b)
          if (x != 0 && t != 1) {
            ans = std::min(ans, 3);
            if ((r + x) * t == c || r + x == c || r * t == c || r == c) ans = std::min(ans, 2);
          }
    return void();
  } 
  bool check1(i32 p, i32 q, i32 r, i32 a, i32 b, i32 c) {
    i32 t;
    if (p == 0) {
      if (a == 0) t = 0;
      else return false;
    } else t = a / p;
    if (p * t != a) return false;
    if ((b - q * t) == (c - r)) return true;
    return false;
  }
  bool check2(i32 p, i32 q, i32 r, i32 a, i32 b, i32 c) {
    i32 t;
    if (!p) {
      if (a == 0) t = 0;
      else return false;
    }
    else t = (a / p);
    if (t * p != a) return false;
    i32 x = c - r;
    if ((q + x) * t == b) return true;
    if (q * t + x == b) return true;
    return false;
  }
  bool check3(i32 p, i32 q, i32 r, i32 a, i32 b, i32 c) {
    i32 t1, t2;
    if (!p) {
      if (a == 0) t1 = 0;
      else return false;
    } else t1 = a / p;
    if (!q) {
      if (b == 0) t2 = 0;
      else return false;
    } else t2 = b / q;
    if (p * t1 != a) return false;
    if (q * t2 != b) return false;
    if (r * t1 * t2 == c) return true;
    return false;
  }
  void solve() {
    p = read(), q = read(), r = read();
    a = read(), b = read(), c = read();
    ans = 3;
    
    if (a - p == b - q || b - q == c - r || a - p == c - r) ans = std::min(ans, 2);
    if (a - p == b - q && b - q == c - r) ans = std::min(ans, 1);
    
    if (a == p) ans = std::min(ans, 2);
    if (b == q) ans = std::min(ans, 2);
    if (c == r) ans = std::min(ans, 2);
    if (a == p && b == q) ans = std::min(ans, 1);
    if (a == p && c == r) ans = std::min(ans, 1);
    if (b == q && c == r) ans = std::min(ans, 1);
    if (a == p && b == q && c == r) ans = std::min(ans, 0);
    if (a == p && b - q == c - r) ans = std::min(ans, 1);
    if (b == q && a - p == c - r) ans = std::min(ans, 1);
    if (c == r && a - p == b - q) ans = std::min(ans, 1);
    
    if ((a - p) + (b - q) == c - r) ans = std::min(ans, 2);
    if ((a - p) + (c - r) == b - q) ans = std::min(ans, 2);
    if ((b - q) + (a - p) == c - r) ans = std::min(ans, 2);
    if ((b - q) + (c - r) == a - p) ans = std::min(ans, 2);
    if ((c - r) + (a - p) == b - q) ans = std::min(ans, 2);
    if ((c - r) + (b - q) == a - p) ans = std::min(ans, 2);
    
    if (check1(p, q, r, a, b, c)) ans = std::min(ans, 2); if (check1(p, r, q, a, c, b)) ans = std::min(ans, 2);
    if (check1(q, p, r, b, a, c)) ans = std::min(ans, 2); if (check1(q, r, p, b, c, a)) ans = std::min(ans, 2);
    if (check1(r, p, q, c, a, b)) ans = std::min(ans, 2); if (check1(r, q, p, c, b, a)) ans = std::min(ans, 2);
    
    if (check2(p, q, r, a, b, c)) ans = std::min(ans, 2); if (check2(p, r, q, a, c, b)) ans = std::min(ans, 2);
    if (check2(q, p, r, b, a, c)) ans = std::min(ans, 2); if (check2(q, r, p, b, c, a)) ans = std::min(ans, 2);
    if (check2(r, p, q, c, a, b)) ans = std::min(ans, 2); if (check2(r, q, p, c, b, a)) ans = std::min(ans, 2);
    
    if (check3(p, q, r, a, b, c)) ans = std::min(ans, 2); if (check3(p, r, q, a, c, b)) ans = std::min(ans, 2);
    if (check3(q, p, r, b, a, c)) ans = std::min(ans, 2); if (check3(q, r, p, b, c, a)) ans = std::min(ans, 2);
    if (check3(r, p, q, c, a, b)) ans = std::min(ans, 2); if (check3(r, q, p, c, b, a)) ans = std::min(ans, 2);
    
    i32 x1 = calc(p, q, a, b); // p & q
    i32 x2 = calc(p, r, a, c); // p & r
    i32 x3 = calc(q, r, b, c); // q & r
    solve1(p, q, r, a, b, c, x1);
    solve1(p, r, q, a, c, b, x2);
    solve1(q, r, p, b, c, a, x3);
    
    x1 = calc2(p, q, a, b); // p & q
    x2 = calc2(p, r, a, c); // p & r
    x3 = calc2(q, r, b, c); // q & r
    solve2(p, q, r, a, b, c, x1);
    solve2(p, r, q, a, c, b, x2);
    solve2(q, r, p, b, c, a, x3);

    fprintf(fout, "%d\n", ans);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("triple.in", "r");
    // fout = fopen("triple.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_triple::main(), 0; }