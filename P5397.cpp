#include <bits/stdc++.h>
namespace FileHeader {
  using int16 = int16_t;
  using int32 = int32_t;
  using int64 = int64_t;
  using uint32 = uint32_t;
  using uint64 = uint64_t;
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  int32 read() {
    int32 t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
  class Iterator {
    public:
      Iterator(int32 _val = 0): _val(_val) {}
      bool operator !=(const Iterator &other) const { return this->_val != other._val; }
      int32 operator *() { return this->_val; }
      int32 operator ++() { return ++this->_val; }
    private:
      int32 _val;
  };
  class Range {
    public:
      Range(int32 _l = 0, int32 _r = 0): _begin(_l), _end(_r + 1) {}
      Iterator begin() { return Iterator(this->_begin); }
      Iterator end() { return Iterator(this->_end); }
    private:
      int32 _begin, _end;
  };
}
using namespace FileHeader;
namespace Solution_Of_P5397 {
  static const int32 N = 100010, B = 255, M = N / B + 10;
  static const int32 inf32 = 0x3f3f3f3f;
  int32 n, m, bl;
  int32 a[N];
  int32 L[M], R[M], len[M];
  int16 ins[N][M];
  int16 inp[N][M];
  int32 fir[N], sec[N];
  template<typename T>
  inline void cmin(T &x, T y) { return x = (x < y ? x : y), void(); }
  template<typename T>
  inline void cmax(T &x, T y) { return x = (x > y ? x : y), void(); }
  inline void init(int32 bl, int32 l, int32 r) {
    L[bl] = l, R[bl] = r;
    std::vector<int32> numric;
    for (auto i : Range(l, r)) numric.eb(a[i]);
    std::sort(all(numric), [&](int32 a, int32 b) { return a < b; });
    numric.erase(std::unique(all(numric)), numric.end());
    int32 res = 0;
    for (auto i : numric) {
      ++res;
      inp[i][bl] = res;
    } 
    for (int32 i = r; i >= l; --i) fir[R[bl - 1] + inp[a[i]][bl]] = i;
    for (int32 i = l; i <= r; ++i) sec[R[bl - 1] + inp[a[i]][bl]] = i;
    len[bl] = static_cast<int32>(numric.size());
    for (int32 i = 1; i <= len[bl]; ++i)
      std::memset(ins[R[bl - 1] + i], 64, (len[bl] + 1) << 1);
    for (auto i : Range(l, r))
      for (auto j : Range(i + 1, r)) {
        int32 a1 = inp[a[i]][bl], a2 = inp[a[j]][bl];
        if (a1 > a2) std::swap(a1, a2);
        cmin(ins[R[bl - 1] + a1][a2], int16(j - i));
      }
    return void();
  }
  inline int32 trans(int16 x) {
    if (x == 0x3f3f) return 0x3f3f3f3f;
    return static_cast<int32>(x);
  }
  inline int32 query(int32 x, int32 y) {
    if (x == y) {
      for (auto i : Range(1, bl))
        if (inp[x][i]) return 0;
      return 0x3f3f3f3f;
    }
    int32 ans = inf32;
    for (auto i : Range(1, bl)) {
      int16 a1 = inp[x][i - 1], a2 = inp[y][i - 1];
      int16 a3 = inp[x][i], a4 = inp[y][i];
      if (a3 > a4) std::swap(a3, a4);
      if (a3 && a4) cmin(ans, trans(ins[R[i - 1] + a3][a4]));
      if (i > 1 && a1 && a4 && sec[R[i - 2] + a1]) cmin(ans, fir[R[i - 1] + a4] - sec[R[i - 2] + a1]);
      if (i > 1 && a2 && a3 && sec[R[i - 2] + a2]) cmin(ans, fir[R[i - 1] + a3] - sec[R[i - 2] + a2]);
    }
    return ans;
  }
  inline void modify1(int32 bl, int32 x, int32 y) {
    inp[y][bl] = inp[x][bl];
    inp[x][bl] = 0;
    return void();
  }
  inline void modify2(int32 bl, int32 x, int32 y) {
    int16 a1 = inp[x][bl], a2 = inp[y][bl];
    cmin(fir[R[bl - 1] + a2], fir[R[bl - 1] + a1]);
    cmax(sec[R[bl - 1] + a2], sec[R[bl - 1] + a1]);
    if (a1 < a2) {
      for (auto i : Range(1, a1 - 1)) cmin(ins[R[bl - 1] + i][a2], ins[R[bl - 1] + i][a1]);
      for (auto i : Range(a1, a2 - 1)) cmin(ins[R[bl - 1] + i][a2], ins[R[bl - 1] + a1][i]);
      for (auto i : Range(a2, len[bl])) cmin(ins[R[bl - 1] + a2][i], ins[R[bl - 1] + a1][i]);
    } else {
      for (auto i : Range(1, a2 - 1)) cmin(ins[R[bl - 1] + i][a2], ins[R[bl - 1] + i][a1]);
      for (auto i : Range(a2, a1 - 1)) cmin(ins[R[bl - 1] + a2][i], ins[R[bl - 1] + i][a1]);
      for (auto i : Range(a1, len[bl])) cmin(ins[R[bl - 1] + a2][i], ins[R[bl - 1] + a1][i]);
    }
    inp[x][bl] = 0;
    return void();
  }
  inline void modify(int32 x, int32 y) {
    for (auto i : Range(1, bl)) {
      if (x == y) continue;
      if (!inp[x][i]) continue;
      if (!inp[y][i]) modify1(i, x, y);
      else modify2(i, x, y);  
    }
    return void();
  }
  inline void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("data.in", "r");
    // fout = fopen("data.out", "w");
    n = read(), m = read();
    for (auto i : Range(1, n)) a[i] = read();
    bl = (n - 1) / B + 1;
    for (auto i : Range(1, bl)) init(i, (i - 1) * B + 1, std::min(n, i * B));
    for (auto t : Range(1, m)) {
      static int32 op, x, y, lastans = 0;
      op = read(), x = read() ^ lastans, y = read() ^ lastans; 
      if (op == 1) modify(x, y);
      if (op == 2) {
        lastans = query(x, y);    
        if (lastans == inf32) lastans = 0, fputs("Ikaros\n", fout);
        else fprintf(fout, "%d\n", lastans);
      }  
    }
    return void();
  }
}
signed main() { return Solution_Of_P5397::main(), 0; }