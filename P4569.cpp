#pragma region
#include <bits/stdc++.h>
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;
#define ep emplace
#define eb emplace_back
#define all(x) x.begin(), x.end()
FILE *fin, *fout, *ferr;
i32 read() {
  i32 t = 0, f = 0;
  char ch = fgetc(fin);
  for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
  for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
  return f ? -t : t;
}
template<typename T1, typename T2>
constexpr bool chkmax(T1 &a, T2 b) { return a > b ? false : (a = b, true); } 
template<typename T1, typename T2>
constexpr bool chkmin(T1 &a, T2 b) { return a > b ? (a = b, true) : false; } 
#pragma endregion
namespace Solution_Of_P4569 {
  bool _1;
  static const i32 M = 5 * 15 + 5;
  i32 n, len, alpha;
  char s[M];
  i32 ch[M][26], fail[M];
  bool tab[M];
  template<i32 N, i32 M>
  struct mat {
    double a[N][M];
    mat() { std::memset(a, 0, sizeof a); }
    const double* operator [](const i32 x) const { return a[x]; }
    double* operator [](i32 x) { return a[x]; }
    template<i32 K>
    mat<N, K> operator *(const mat<M, K> &other) {
      mat<N, K> ret;
      for (i32 i = 0; i < N; ++i)
        for (i32 j = 0; j < K; ++j)
          for (i32 k = 0; k < M; ++k)
            ret[i][j] += this->a[i][k] * other[k][j];
      return ret;
    }
    void reset(mat<N, M> &a) {
      for (i32 i = 0; i < N; ++i)
        for (i32 j = 0; j < N; ++j)
          a[i][j] = (i == j);
      return void();
    }
    mat<N, M> operator ^(const i32 k) {
      i32 _k = k;
      mat<N, M> ans, m = *this;
      reset(ans);
      if (k == 0) return ans;
      if (k == 1) return *this;
      for (; _k; _k >>= 1, m = m * m)
        if (_k & 1) ans = ans * m;
      return ans;
    }
  };
  bool _2;
  i32 tot = 1;
  void insert(i32 n, char *s) {
    i32 p = 1;
    for (i32 i = 1; i <= n; ++i) {
      i32 c = s[i] - 'a';
      if (!ch[p][c]) ch[p][c] = ++tot;  
      p = ch[p][c];
    }
    tab[p] = true;
    return void();
  }
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    n = read(), len = read(), alpha = read();
    for (i32 i = 1; i <= n; ++i) {
      fscanf(fin, "%s", s + 1);
      insert(strlen(s + 1), s);
    }
    std::queue<i32> q;
    for (i32 i = 0; i < alpha; ++i)
      ch[0][i] = 1;
    fail[1] = 0;
    q.ep(1);
    while (q.size()) {
      i32 u = q.front(); q.pop();
      tab[u] |= tab[fail[u]];
      for (i32 i = 0; i < alpha; ++i) {
        if (ch[u][i]) {
          fail[ch[u][i]] = ch[fail[u]][i];
          q.ep(ch[u][i]);
        } else ch[u][i] = ch[fail[u]][i];
      }
    }
    mat<80, 80> base;
    for (i32 i = 1; i <= tot; ++i) {
      for (i32 j = 0; j < alpha; ++j) {
        if (tab[ch[i][j]]) {
          base[i - 1][0] += 1.0 / alpha;
          base[i - 1][tot] += 1.0 / alpha;
        } else {
          base[i - 1][ch[i][j] - 1] += 1.0 / alpha;
        }
      }
    }
    base[tot][tot] = 1.0;
    base = base ^ len;
    fprintf(fout, "%.8lf\n", base[0][tot]);
    i64 Start_Time_Without_Read = clock();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_P4569::main(), 0; }