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
namespace Solution_Of_sort {
  bool _1;
#pragma endregion
  static const i32 N = 700005, M = N * 32;
  i32 n, tot;
  i32 a[N], b[N];
  i32 rt[N], ls[M], rs[M], cnt[M];
  bool _2;
  i32 NewNode() { return ++tot; }
  void pushup(i32 x) { return cnt[x] = cnt[ls[x]] + cnt[rs[x]], void(); }
  void change(i32 &x, i32 y, i32 l, i32 r, i32 p) {
    x = NewNode();
    cnt[x] = cnt[y], ls[x] = ls[y], rs[x] = rs[y];
    if (l == r) {
      ++cnt[x];
      return void();
    }
    i32 mid((l + r) >> 1);
    if (p <= mid)
      change(ls[x], ls[y], l, mid, p);
    else
      change(rs[x], rs[y], mid + 1, r, p);
    return pushup(x);
  }
  i32 query(i32 x, i32 y, i32 l, i32 r, i32 v) {
    if (l == r) return l;
    i32 mid((l + r) >> 1);
    if (cnt[ls[x]] - cnt[ls[y]] >= v) return query(ls[x], ls[y], l, mid, v);
    return query(rs[x], rs[y], mid + 1, r, v - (cnt[ls[x]] - cnt[ls[y]]));
  }
  i64 sort(i32 l, i32 r) {
    if (l >= r) return 0;
    i32 p = query(rt[r], rt[l - 1], 1, n, (r - l + 2) / 2);
    // fprintf(fout, "now [%d %d]\n", l, r);
    // fprintf(fout, "[%d %d] and [%d %d]\n", l, a[p] - 1, a[p] + 1, r);
    return r - l + 1 + sort(l, a[p] - 1) + sort(a[p] + 1, r);
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    i64 Start_Time_Without_Read = clock();
    std::iota(b + 1, b + n + 1, 1);
    std::sort(b + 1, b + n + 1, [&](const i32 &x, const i32 &y) { return a[x] < a[y]; });
    rt[0] = NewNode();
    for (i32 i = 1; i <= n; ++i) change(rt[i], rt[i - 1], 1, n, b[i]);
    fprintf(fout, "%lld\n", sort(1, n));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_sort::main(), 0; }