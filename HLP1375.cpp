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
namespace Solution_Of_HLP1375 {
  bool _1;
#pragma endregion
  static const i32 N = 200005;
  static const i64 inf64 = 4000000001;
  i32 n;
  i64 a[N];
  i64 ans;
  bool _2;
  struct SegmentTree {
    struct Matrix {
      i64 a[2][2];
      Matrix() = default;
      Matrix(i64 _a, i64 _b, i64 _c, i64 _d) {
        a[0][0] = _a, a[0][1] = _b;
        a[1][0] = _c, a[1][1] = _d;
      }
      i64* operator [](i32 x) & { return a[x]; }
      const i64* operator [](i32 x) const & { return a[x]; }
      Matrix operator *(const Matrix &other) const {
        Matrix ret = Matrix(inf64, inf64, inf64, inf64);
        for (i32 i = 0; i < 2; ++i)
          for (i32 j = 0; j < 2; ++j)
            for (i32 k = 0; k < 2; ++k)
              ret[i][j] = std::min(ret[i][j], std::max(this->a[i][k], other[k][j]));
        return ret;
      }
    } tr[N << 2];
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    void pushup(i32 x) {
      tr[x] = tr[ls] * tr[rs];
      return void();
    }
    void build(i32 x, i32 l, i32 r) {
      if (l == r) {
        tr[x] = Matrix(a[l], a[l] + a[l + 1], 0, inf64);
        return void();
      }
      i32 mid((l + r) >> 1);
      build(ls, l, mid);
      build(rs, mid + 1, r);
      return pushup(x);
    }
    void modify(i32 x, i32 l, i32 r, i32 p) {
      if (l == r) {
        tr[x][0][0] = inf64;
        return void();
      }
      i32 mid((l + r) >> 1);
      if (p <= mid) modify(ls, l, mid, p);
      else modify(rs, mid + 1, r, p);
      return pushup(x);
    }
    void change(i32 x, i32 l, i32 r, i32 p) {
      if (l == r) {
        tr[x][0][1] = inf64;
        return void();
      }
      i32 mid((l + r) >> 1);
      if (p <= mid) change(ls, l, mid, p);
      else change(rs, mid + 1, r, p);
      return pushup(x);
    }
  } seg;
  std::vector<i32> hash;
  std::vector<std::array<i32, 2>> pos[N * 2];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    a[n + 1] = inf64;
    seg.build(1, 1, n);
    for (i32 i = 1; i <= n; ++i) hash.eb(a[i]);
    for (i32 i = 1; i < n; ++i) hash.eb(a[i] + a[i + 1]);
    std::sort(all(hash));
    hash.erase(std::unique(all(hash)), hash.end());
    for (i32 i = 1; i <= n; ++i) {
      i32 p = std::lower_bound(all(hash), a[i]) - hash.begin();
      pos[p].push_back({i, 0});
    }
    for (i32 i = 1; i < n; ++i) {
      i32 p = std::lower_bound(all(hash), a[i] + a[i + 1]) - hash.begin();
      pos[p].push_back({i, 1});
    }
    ans = inf64;
    for (i32 i = 0; i < hash.size(); ++i) {
      ans = std::min(ans, seg.tr[1][0][0] - hash[i]);
      for (auto &[p, q] : pos[i])
        if (q == 0) seg.modify(1, 1, n, p);
        else seg.change(1, 1, n, p);
    }
    fprintf(fout, "%lld\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1375::main(), 0; }