#include <bits/stdc++.h>
namespace FileHeader {
  using int32 = int32_t;
  using int64 = int64_t;
  using uint32 = uint32_t;
  using uint64 = uint64_t;
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  int64 read() {
    int64 t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
}
using namespace FileHeader;
namespace Solution_Of_HLP1288 {
  static const int32 N = 100005;
  int32 n, m;
  std::array<int64, 2> market[N];
  int64 sum[N], sum2[N];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    n = read(), m = read();
    for (int32 i = 1; i <= n; ++i) {
      market[i][0] = read();
      market[i][1] = read();
    }
    std::sort(market + 1, market + n + 1, [&](const std::array<int64, 2> &a, const std::array<int64, 2> &b)
      {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] < b[1];
      });
    for (int32 i = 1; i <= n; ++i) {
      sum[i] = sum[i - 1] + market[i][0];
      sum2[i] = sum2[i - 1] + market[i][1];
    }
    for (int32 t = 1; t <= m; ++t) {
      int64 now = read();
      int32 lst = n + 1;
      int64 ans = 0;
      while (true) {
        int32 l = 1, r = lst - 1, p = -1;
        while (l <= r) {
          int32 mid((l + r) >> 1);
          if (market[mid][0] <= now) l = mid + 1, p = mid;
          else r = mid - 1;
        }
        if (p == -1) break;
        l = 1, r = p;
        int32 o = -1;
        while (l <= r) {
          int32 mid((l + r) >> 1);
          if (sum[p] - sum[mid - 1] <= now) r = mid - 1, o = mid;
          else l = mid + 1;
        }
        ans += sum2[p] - sum2[o - 1];
        now -= sum[p] - sum[o - 1];
        lst = o - 1;
      }
      fprintf(fout, "%ld\n", ans);
    }
    return void();
  }
}
signed main() { return Solution_Of_HLP1288::main(), 0; }