#pragma GCC optimize(3)
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
  static const i32 N = 10005, K = 15;
  static const i32 P = 998244353;
  i32 inc(i32 x, i32 y) { return (x + y) % P; }
  template<typename ...Args>
  i32 inc(i32 x, Args ...args) { return inc(x, inc(args...)); }
  i32 dec(i32 x, i32 y) { return (x + P - y) % P; }
  i32 mul(i32 x, i32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  i32 mul(i32 x, Args ...args) { return mul(x, mul(args...)); }
  i32 qpow(i32 x, i32 y) {
    i32 ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
      if (y & 1) ans = mul(ans, x);
    return ans;
  }
  i32 n, m, tot, ans;
  i32 a[N], b[N];
  bool _2;
  bool _mid(i32 v1, i32 v2, i32 v3) {
    if (v1 <= v2 && v2 <= v3) return true;
    if (v3 <= v2 && v2 <= v1) return true;
    return false;
  }
  i32 _getmid(i32 v1, i32 v2, i32 v3) {
    if (_mid(v2, v1, v3) && _mid(v3, v1, v2)) return v1;
    if (_mid(v1, v2, v3) && _mid(v3, v2, v1)) return v2;
    if (_mid(v1, v3, v2) && _mid(v2, v3, v1)) return v3;
    return -1;
  }
  i32 size[N];
  i32 dp[N * 9][K][K][3];
  void dfs(i32 x, i32 l, i32 r, i32 v) {
    i32 nn = (r - l + 1);
    size[x] = 0;
    if (nn == 1) {
      if (a[l] == -1) {
        size[x] = 1;
        if (v > 0) dp[x][1][0][0] = 1;
        dp[x][0][1][1] = 1;
        if (v < m) dp[x][0][0][2] = 1;
      }
      else dp[x][0][0][b[l] + 1] = 1, size[x] = 0;
      return void();
    }
    if (nn == 2) {
      if (a[l] == -1 && a[r] == -1) {
        size[x] = 2;
        // 1 and -1 -> 0
        if (v < m && v > 0) dp[x][1][0][0] += 1;
        // 1 and 0 -> 1
        if (v < m) dp[x][0][1][1] += 1;
        // 1 and 1 -> 2
        if (v < m) dp[x][0][0][2] += 1;

        // 0 and -1 -> 0
        if (v > 0) dp[x][1][1][0] += 1;
        // 0 and 0 -> 1
        dp[x][0][2][1] += 1;
        // 0 and 1 -> 1
        if (v < m) dp[x][0][1][1] += 1;

        // -1 and -1 -> 0
        if (v > 0)
        dp[x][2][0][0] += 1;
        // -1 and 0 -> 0
        if (v > 0)
        dp[x][1][1][0] += 1;
        // -1 and 1 -> 0
        if (v < m && v > 0)
        dp[x][1][0][0] += 1;
      } else if (a[l] == -1) {
        size[x] = 1;
        if (b[r] == -1) {
          if (v > 0) dp[x][1][0][0] = 1;
          dp[x][0][1][0] = 1;
          if (v < m) dp[x][0][0][0] = 1;
        }
        if (b[r] == 0) {
          if (v > 0) dp[x][1][0][0] = 1;
          dp[x][0][1][1] = 1;
          if (v < m) dp[x][0][0][1] = 1;
        }
        if (b[r] == 1) {
          if (v > 0) dp[x][1][0][0] = 1;
          dp[x][0][1][1] = 1;
          if (v < m) dp[x][0][0][2] = 1;
        }
      } else if (a[r] == -1) {
        size[x] = 1;
        if (b[l] == -1) {
          if (v > 0) dp[x][1][0][0] = 1;
          dp[x][0][1][0] = 1;
          if (v < m) dp[x][0][0][0] = 1;
        }
        if (b[l] == 0) {
          if (v > 0) dp[x][1][0][0] = 1;
          dp[x][0][1][1] = 1;
          if (v < m) dp[x][0][0][1] = 1;
        }
        if (b[l] == 1) {
          if (v > 0) dp[x][1][0][0] = 1;
          dp[x][0][1][1] = 1;
          if (v < m) dp[x][0][0][2] = 1;
        }
      } else {
        size[x] = 0;
        i32 middle = std::min(b[l], b[r]);
        dp[x][0][0][middle + 1] = 1;
      }
      return void();
    }
    i32 left = (nn + 2) / 3;
    i32 right = nn - nn / 3;
    std::tuple<i32, i32, i32> ch[3] = {{l, l + left - 1, x * 3 - 1}, {l + left, l + right - 1, x * 3}, {l + right, r, x * 3 + 1}};
    i32 g[K][K][4][4] = {}, h[K][K][4][4] = {};
    for (auto [L, R, y] : ch) {
      dfs(y, L, R, v);
      if (y == x * 3 - 1) {
        for (i32 i = 0; i <= size[y]; ++i)
          for (i32 j = 0; i + j <= size[y]; ++j) {
            g[i][j][1][0] = dp[y][i][j][0];
            g[i][j][0][1] = dp[y][i][j][1];
            g[i][j][0][0] = dp[y][i][j][2];
          }
        size[x] += size[y];
      } else {
        i32 now = y - (x * 3 - 1) + 1;
        for (i32 i = 0; i <= size[x]; ++i)
          for (i32 j = 0; i + j <= size[x]; ++j)
            for (i32 ii = 0; ii <= size[y]; ++ii)
              for (i32 jj = 0; ii + jj <= size[y]; ++jj)
                for (i32 k = 0; k <= now - 1; ++k)
                  for (i32 o = 0; o + k <= now - 1; ++o) {
                    if (k + 1 <= now) h[i + ii][j + jj][k + 1][o] = inc(mul(dp[y][ii][jj][0], g[i][j][k][o]), h[i + ii][j + jj][k + 1][o]);
                    if (o + 1 <= now) h[i + ii][j + jj][k][o + 1] = inc(mul(dp[y][ii][jj][1], g[i][j][k][o]), h[i + ii][j + jj][k][o + 1]);
                    h[i + ii][j + jj][k][o] = inc(mul(dp[y][ii][jj][2], g[i][j][k][o]), h[i + ii][j + jj][k][o]);
                  }
        size[x] += size[y];
        for (i32 i = 0; i <= size[x]; ++i)
          for (i32 j = 0; i + j <= size[x]; ++j)
            for (i32 k = 0; k <= now; ++k)
              for (i32 o = 0; o + k <= now; ++o)
                g[i][j][k][o] = h[i][j][k][o], h[i][j][k][o] = 0;
      }
    }
    for (i32 i = 0; i <= size[x]; ++i)
      for (i32 j = 0; i + j <= size[x]; ++j) {
        dp[x][i][j][0] = inc(dp[x][i][j][0], g[i][j][2][0], g[i][j][2][1], g[i][j][3][0]);
        dp[x][i][j][1] = inc(dp[x][i][j][1], g[i][j][0][2], g[i][j][1][2], g[i][j][0][3], g[i][j][1][1]);
        dp[x][i][j][2] = inc(dp[x][i][j][2], g[i][j][0][0], g[i][j][0][1], g[i][j][1][0]);
      }
    return void();
  }
  i32 cnt[3];
  i32 ret;
  i32 find(i32 l, i32 r) {
    i32 nn = (r - l + 1);
    if (nn <= 2) {
      if (nn == 1) return b[l];
      else return std::min(b[l], b[r]);
    }
    i32 left = (nn + 2) / 3;
    i32 right = nn - nn / 3;
    i32 v1 = find(l + 1 - 1, l + left - 1);
    i32 v2 = find(l + (left + 1) - 1, l + right - 1);
    i32 v3 = find(l + (right + 1) - 1, l + nn - 1);
    return _getmid(v1, v2, v3);
    return -1;
  }
  void dfs(i32 x, i32 sa, i32 sb, i32 nowa, i32 nowb, i32 v) {
    if (x == n + 1) {
      if (nowa == sa && nowb == sb && find(1, n) == 0) {
        ret = inc(ret, mul(qpow(v, sa), qpow(m - v, tot - sa - sb)));
      }
      return void();
    }
    if (a[x] == -1) {
      for (i32 i = -1; i <= 1; ++i) {
        b[x] = i;
        dfs(x + 1, sa, sb, nowa + (b[x] == -1), nowb + (b[x] == 0), v);
      }
    } else {
      dfs(x + 1, sa, sb, nowa, nowb, v);
    }
  }
  void _Dynamic(i32 x) {
    std::memset(dp, 0, sizeof dp);
    cnt[0] = cnt[1] = cnt[2] = 0;
    for (i32 i = 1; i <= n; ++i) {
      if (a[i] == -1) continue;
      if (a[i] < x) b[i] = -1;
      if (a[i] == x) b[i] = 0;
      if (a[i] > x) b[i] = 1;
      ++cnt[b[i] + 1];
    }
    dfs(1, 1, n, x);
    size[1] = tot;
    #define Dp
    if (x < m) {
      for (i32 i = 0; i <= (x == 0 ? 0 : size[1]); ++i) // -1
        for (i32 j = 0; i + j <= size[1]; ++j) // 0
          if (cnt[0] + i < (n + 1) / 2 && cnt[0] + cnt[1] + i + j >= (n + 1) / 2) {
            #ifdef Dp
            ans = inc(ans, mul(qpow(x, i), qpow(m - x, size[1] - i - j), dp[1][i][j][1]));
            #else
            ret = 0;
            dfs(1, i, j, 0, 0, x);
            fprintf(fout, "%d %d %d %d\n", x, i, j, ret);
            ans += ret;
            #endif
          }
    } else {
      for (i32 i = 0; i <= size[1]; ++i) {
        i32 j = size[1] - i;
        if (cnt[0] + i < (n + 1) / 2 && cnt[0] + cnt[1] + i + j >= (n + 1) / 2) {
          #ifdef Dp
          ans = inc(ans, mul(qpow(x, i), qpow(m - x, size[1] - i - j), dp[1][i][j][1]));
          #else
          ret = 0;
          dfs(1, i, j, 0, 0, x);
          fprintf(fout, "%d %d %d %d\n", x, i, j, ret);
          ans += ret;
          #endif
        }
      }
    }
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("data.in", "r");
    // fout = fopen("data.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), m = read();
    i64 Start_Time_Without_Read = clock();
    for (i32 i = 1; i <= n; ++i) a[i] = read();
    for (i32 i = 1; i <= n; ++i) if (a[i] == -1) ++tot;
    for (i32 x = 0; x <= m; ++x) _Dynamic(x);
    fprintf(fout, "%d\n", mul(ans, qpow(qpow(m + 1, tot), P - 2)));
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1381::main(), 0; }