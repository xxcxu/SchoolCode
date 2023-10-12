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
namespace Solution_Of_CF453E {
  bool _1;
#pragma endregion
  static const i32 N = 100005, B = 400, M = N / B + 5;
  static const i32 T = 100000;
  i32 n;
  i64 x[N], m[N], k[N];
  i32 bel[N], L[M], R[M], lst[N];
  i64 f[M][T + 5];
  i32 limit[M];
  namespace blk {
    void init() {
      for (i32 i = 1; i <= n; ++i) {
        bel[i] = (i - 1) / B + 1;
        if (!L[bel[i]]) L[bel[i]] = i;
        R[bel[i]] = i;
      }
      for (i32 i = 1; i <= bel[n]; ++i) {
        f[i][0] = 0;
        for (i32 j = L[i]; j <= R[i]; ++j) {
          if (!k[j]) continue;
          f[i][1] += k[j];
          f[i][m[j] / k[j] + 1] -= k[j];
        }
        for (i32 j = 1; j <= T; ++j) f[i][j] += f[i][j - 1];
        for (i32 j = L[i]; j <= R[i]; ++j) {
          if (!k[j]) continue;
          f[i][m[j] / k[j] + 1] += m[j] % k[j];
        }
        for (i32 j = 1; j <= T; ++j) f[i][j] += f[i][j - 1];
        limit[i] = true;
      }
      return void();
    }
    i64 change(i32 p, i32 l, i32 r, i32 t) {
      i64 ans = 0;
      if (limit[p]) {
        for (i32 i = l; i <= r; ++i) {
          ans += std::min(m[i], x[i] + k[i] * (t - lst[i]));
          x[i] = 0;
          lst[i] = t;
        }
      } else {
        limit[p] = true;
        i32 ti = lst[L[p]];
        for (i32 i = l; i <= r; ++i) {
          ans += std::min(m[i], k[i] * (t - ti));
          x[i] = 0;
          lst[i] = t;
        }
        for (i32 i = L[p]; i < l; ++i) x[i] = 0, lst[i] = ti;
        for (i32 i = r + 1; i <= R[p]; ++i) x[i] = 0, lst[i] = ti;
      }
      return ans;
    }
    i64 query(i32 l, i32 r, i32 t) {
      i32 p = bel[l], q = bel[r];
      if (p == q) {
        return change(p, l, r, t);
      } else {
        i64 ans = 0;
        ans += change(p, l, R[p], t);
        ans += change(q, L[q], r, t);
        for (i32 i = p + 1; i < q; ++i) {
          if (limit[i]) {
            for (i32 j = L[i]; j <= R[i]; ++j)
              ans += std::min(m[j], x[j] + k[j] * (t - lst[j]));
            limit[i] = false;
            lst[L[i]] = t;
          } else {
            ans += f[i][std::min(T, t - lst[L[i]])];
            lst[L[i]] = t;
          }
        }
        return ans;
      }
    } 
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) x[i] = read(), m[i] = read(), k[i] = read();
    i64 Start_Time_Without_Read = clock();
    blk::init();
    i32 m = read();
    while (m--) {
      static i32 t, l, r;
      t = read(), l = read(), r = read();
      fprintf(fout, "%lld\n", blk::query(l, r, t));
    }
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF453E::main(), 0; }