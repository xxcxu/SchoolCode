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
namespace Solution_Of_CF1879F {
  bool _1;
  static const i32 N = 200005, V = N;
  i32 n; i64 ans[N];
  struct heros {
    i32 c, hp;
    heros() = default;
    heros(i32 c, i32 hp): c(c), hp(hp) {}
  } a[N];
  struct Node {
    i32 c, id;
    Node() = default;
    Node(i32 c, i32 id): c(c), id(id) {}
    bool operator <(const Node &other) const { return this->c < other.c; }
    bool operator ==(const Node &other) const { return this->c == other.c && this->id == other.id; }
    bool operator <=(const Node &other) const { return (*this) < other || (*this) == other; }
  };
  struct VNode {
    Node a[2];
    VNode() = default;
    VNode(Node x, Node y) { a[0] = x, a[1] = y; }
    void merge(const Node &other) {
      if (this->a[0] <= other) {
        this->a[1] = this->a[0];
        this->a[0] = other;
      } else if (this->a[1] < other)
        this->a[1] = other;
      return void();
    }
    void merge(const VNode &other) {
      this->merge(other.a[0]);
      this->merge(other.a[1]);
      return void();
    }
  } b[N];
  bool _2;
  void solve() {
    n = read();
    std::memset(ans, 0, sizeof ans);
    for (i32 i = 1; i < V; ++i) b[i] = VNode();
    for (i32 i = 1; i <= n; ++i) a[i].c = read();
    for (i32 i = 1; i <= n; ++i) a[i].hp = read();
    for (i32 i = 1; i <= n; ++i) {
      Node v = Node(a[i].c, i);
      b[a[i].hp].merge(v);
    }
    for (i32 i = V - 1; i > 1; --i) b[i - 1].merge(b[i]);
    for (i32 i = 1; i < V; ++i) {
      i64 max = -1, minimax = -1, l = -1;
      for (i32 j = 1; j < V; j += i) {
        i64 v = 1ll * ((j - 1) / i + 1) * b[j].a[0].c;
        if (v > max) max = v, l = j;
      }
      for (i32 j = 1; j < V; j += i) {
        i64 v = 1ll * ((j - 1) / i + 1) * b[j].a[b[j].a[0] == b[l].a[0]].c;
        if (v > minimax) minimax = v;
      }
      ans[b[l].a[0].id] = std::max(ans[b[l].a[0].id], max - minimax);
    }
    for (i32 i = 1; i <= n; ++i) fprintf(fout, "%lld%c", ans[i], " \n"[i == n]);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1879F::main(), 0; }