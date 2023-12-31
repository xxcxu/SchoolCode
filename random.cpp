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
namespace Solution_Of_ {
  bool _1;
#pragma endregion
  bool _2;
  i32 a[50];
  i32 rnd(i32 l, i32 r) { return 1ll * rand() * rand() % (r - l + 2) + l; }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    srand(time(0));
    fout = fopen("data.in", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 n = rnd(1, 10), m = rnd(1, 10);
    i64 Start_Time_Without_Read = clock();
    fprintf(fout, "%d %d\n", n, m);
    i32 k = 0;
    for (i32 i = 1; i <= n; ++i) {
      i32 op = rnd(0, 1);
      if (op || k > 5) a[i] = rnd(0, m);
      else a[i] = -1, ++k;
      fprintf(fout, "%d ", a[i]);
    }
    fputs("\n", fout);
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_::main(), 0; }