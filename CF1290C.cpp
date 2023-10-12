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
namespace Solution_Of_CF1290C {
  bool _1;
#pragma endregion
  static const i32 N = 300005;
  i32 n, k, ans;
  i32 fir[N], sec[N];
  i32 fa[N], cost[N], cant[N], size[N], tag[N];
  char s[N];
  bool _2;
  i32 find(i32 x) {
    if (!fa[x]) return x;
    if (!fa[fa[x]]) return fa[x];
    i32 f = find(fa[x]);
    tag[x] ^= tag[fa[x]];
    return fa[x] = f;
  }
  void merge(i32 x, i32 y) {
    fa[x] = y;
    cost[y] += cost[x];
    cant[y] |= cant[x];
    size[y] += size[x];
    tag[x] ^= tag[y];
    return void();
  }
  i32 statue(i32 x) { return tag[x] ^ tag[fa[x]]; }
  void use(i32 x) { return ans += cost[x], tag[x] ^= 1, cost[x] = -cost[x], void(); }
  void add(i32 x) {
    if (!fir[x]) return void();
    if (!sec[x]) {
      i32 p = find(fir[x]);
      cant[p] = true;
      if (statue(fir[x]) == (s[x] - '0')) use(p);
      return void();
    }
    i32 p1 = find(fir[x]), p2 = find(sec[x]);
    if (p1 == p2) return void();
    if (size[p1] > size[p2]) std::swap(p1, p2);
    if ((statue(fir[x]) ^ statue(sec[x])) == (s[x] - '0')) {
      i32 c1 = cost[p1], c2 = cost[p2];
      if ((c1 < c2 && !cant[p1]) || cant[p2]) use(p1);
      else use(p2);
    }
    merge(p1, p2);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), k = read();
    fscanf(fin, "%s", s + 1);
    for (i32 i = 1; i <= k; ++i) {
      static i32 x;
      i32 l = read();
      while (l--) {
        x = read();
        if (fir[x]) sec[x] = i;
        else fir[x] = i;
      }
    }
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= k; ++i) cost[i] = 1, size[i] = 1;
    for (i32 i = 1; i <= n; ++i) add(i), fprintf(fout, "%d\n", ans);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1290C::main(), 0; }