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
namespace Solution_Of_CF1025E {
  bool _1;
  static const int32 N = 55;
  int32 n, m, idx[N];
  int32 vis[N][N];
  struct Node {
    int32 x, y, id;
    Node() = default;
    Node(int32 x, int32 y, int32 id): x(x), y(y), id(id) {}
    void allin(int32 i);
  } s[N], t[N];
  using path_type = std::vector<std::tuple<int32, int32, int32, int32>>;
  path_type path1, path2;
  bool _2;
  void Node::allin(int32 i) { this->x = read(), this->y = read(), this->id = i; }
  void solve(Node *a, path_type &path) {
    auto move = [&](int32 i, int32 tx, int32 ty) {
      while (a[i].x != tx) {
        int32 to_x = a[i].x + (a[i].x < tx ? +1 : -1);
        int32 to_y = a[i].y;
        path.eb(a[i].x, a[i].y, to_x, to_y);
        vis[a[i].x][a[i].y] = false;
        vis[a[i].x = to_x][a[i].y = to_y] = true;
      }
      while (a[i].y != ty) {
        int32 to_x = a[i].x;
        int32 to_y = a[i].y + (a[i].y < ty ? +1 : -1);
        path.eb(a[i].x, a[i].y, to_x, to_y);
        vis[a[i].x][a[i].y] = false;
        vis[a[i].x = to_x][a[i].y = to_y] = true;
      }
      return void();
    };
    std::memset(vis, 0, sizeof vis);
    for (int32 i = 1; i <= n; ++i) vis[a[i].x][a[i].y] = true;
    while (true) {
      bool worked = false;
      for (int32 i = 1; i <= n; ++i) {
        if (a[i].x == i) continue;
        bool flag = false;
        if (a[i].x < i)
          for (int32 j = a[i].x + 1; j <= i; ++j)
            if (vis[j][a[i].y]) flag = true;
        if (a[i].x > i)
          for (int32 j = i; j <= a[i].x - 1; ++j)
            if (vis[j][a[i].y]) flag = true;
        if (flag) continue;
        worked = true;
        move(i, i, a[i].y);
      }
      if (!worked) break;
    }
    for (int32 i = 1; i <= n; ++i) move(i, i, i);
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    m = read(), n = read();
    for (int32 i = 1; i <= n; ++i) s[i].allin(i);
    for (int32 i = 1; i <= n; ++i) t[i].allin(i);
    int64 Start_Time_Without_Read = clock();
    std::sort(s + 1, s + n + 1, [&](const Node &a, const Node &b) { return a.x < b.x; });
    std::sort(t + 1, t + n + 1, [&](const Node &a, const Node &b) { return a.x < b.x; });
    solve(s, path1), solve(t, path2);
    for (int32 i = 1; i <= n; ++i) idx[t[i].id] = i;
    for (int32 i = 1; i <= n; ++i)
      for (int32 j = 2; j <= n; ++j) 
        if (idx[s[j].id] < idx[s[j - 1].id]) {
          path1.eb(j, j, j - 1, j);
          path1.eb(j - 1, j - 1, j, j - 1);
          path1.eb(j, j - 1, j, j);
          path1.eb(j - 1, j, j - 1, j - 1); 
          std::swap(s[j], s[j - 1]);
        }
    std::reverse(all(path2));
    fprintf(fout, "%lld\n", path1.size() + path2.size());
    for (auto [x, y, nx, ny] : path1) fprintf(fout, "%d %d %d %d\n", x, y, nx, ny);
    for (auto [x, y, nx, ny] : path2) fprintf(fout, "%d %d %d %d\n", nx, ny, x, y);
    int64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_CF1025E::main(), 0; }