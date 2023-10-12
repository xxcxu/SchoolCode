#pragma region
#include <bits/stdc++.h>
namespace FileHeader {
  using i16 = int16_t;
  using i32 = int32_t;
  using i64 = int64_t;
  using u32 = uint32_t;
  using u64 = uint64_t;
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
namespace Solution_Of_HLP1381 {
  bool _1;
#pragma endregion
  static const i32 N = 100005;
  static const i32 P = 998244353;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 n, m, res, ans;
  i32 a[N], b[N];
  bool _2;
  bool mid(i32 v1, i32 v2, i32 v3) {
    if (v1 <= v2 && v2 <= v3) return true;
    if (v3 <= v2 && v2 <= v1) return true;
    return false;
  }
  i32 find(i32 l, i32 r) {
    i32 nn = (r - l + 1);
    if (nn <= 2) {
      if (nn == 1) return a[l];
      else return std::min(a[l], a[r]);
    }
    i32 left = (nn + 2) / 3;
    i32 right = nn - nn / 3;
    i32 v1 = find(l + 1 - 1, l + left - 1);
    i32 v2 = find(l + (left + 1) - 1, l + right - 1);
    i32 v3 = find(l + (right + 1) - 1, l + nn - 1);
    if (mid(v2, v1, v3) || mid(v3, v1, v2)) return v1;
    if (mid(v1, v2, v3) || mid(v3, v2, v1)) return v2;
    if (mid(v1, v3, v2) || mid(v2, v3, v1)) return v3;
    return -1;
  }
  i32 find() {
    std::memcpy(b + 1, a + 1, n * sizeof(i32));
    std::sort(b + 1, b + n + 1);
    return b[(n + 1) / 2];
  }
  void dfs(i32 x) {
    if (x == n + 1) {
      if (find(1, n) == find()) ++ans;
      return void();
    }
    if (a[x] != -1) dfs(x + 1);
    else {
      for (i32 i = 0; i <= m; ++i)
        a[x] = i, dfs(x + 1), a[x] = -1;
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("data.in", "r");
    fout = fopen("data.ans", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    i64 Start_Time_Without_Read = clock();
    res = 1;
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) if (a[i] == -1) res = mul(res, m + 1);
    dfs(1);
    fprintf(fout, "%d\n", mul(ans, qpow(res, P - 2)));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1381::main(), 0; }