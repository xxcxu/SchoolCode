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
namespace Solution_Of_HLP1471 {
  bool _1;
  char s[11][10];
  void trans(char &c) {
    if ('A' <= c && c <= 'Z')
      c = c - 'A' + 'a';
    return void();
  }
  /*
  棋盘：坐标集合{(x,y)|x∈[1,10]∩Z,y ∈[1,9]∩Z}
  红方河界：坐标集合{(x,y)|x∈[1,5]∩Z,y ∈[1,9]∩Z}
  黑方河界：坐标集合{(x,y)|x∈[6,10]∩Z,y ∈[1,9]∩Z}
  红方九宫：坐标集合{(x,y)|x∈[1,3]∩Z,y ∈[4,6]∩Z}
  黑方九宫：坐标集合{(x,y)|x∈[8,10]∩Z,y ∈[4,6]∩Z}
  棋子：每个棋子属于红黑双方中的一方且位于棋盘内两两不同的坐标上
  棋子可以移动，移动后的位置上需无己方棋子，且若为对方棋子则将其
  替换为己方所移动的棋子
  */
  bool check(i32 x, i32 y, i32 col) {
    if (col == 0 && 'a' <= s[x][y] && s[x][y] <= 'z') return false;
    if (col == 1 && 'A' <= s[x][y] && s[x][y] <= 'Z') return false;
    return true;
  }
  i32 calc_jiang(i32 x, i32 y, i32 col) {
    static const i32 dx[] = {1, -1, 0, 0};
    static const i32 dy[] = {0, 0, 1, -1};
    i32 ans = 0;
    for (i32 d = 0; d < 4; ++d) {
      i32 tx = x + dx[d], ty = y + dy[d];
      if (col == 0 && !(1 <= tx && tx <=  3 && 4 <= ty && ty <= 6)) continue;
      if (col == 1 && !(8 <= tx && tx <= 10 && 4 <= ty && ty <= 6)) continue;
      if (check(tx, ty, col)) ++ans;
    }
    if (col == 0) {
      bool onLine = true, flag = false;
      for (i32 i = x + 1; i <= 10; ++i) {
        if (s[i][y] != '*' && s[i][y] != 'J') onLine = false;
        if (s[i][y] == 'J') { flag = onLine; break; }
      }
      ans += flag;
    }
    if (col == 1) {
      bool onLine = true, flag = false;
      for (i32 i = x - 1; i >= 1; --i) {
        if (s[i][y] != '*' && s[i][y] != 'j') onLine = false;
        if (s[i][y] == 'j') { flag = onLine; break; }
      }
      ans += flag;
    }
    return ans;
  }
  i32 calc_shi(i32 x, i32 y, i32 col) {
    static const i32 dx[] = {1, 1, -1, -1};
    static const i32 dy[] = {1, -1, 1, -1};
    i32 ans = 0;
    for (i32 d = 0; d < 4; ++d) {
      i32 tx = x + dx[d], ty = y + dy[d];
      if (col == 0 && !(1 <= tx && tx <=  3 && 4 <= ty && ty <= 6)) continue;
      if (col == 1 && !(8 <= tx && tx <= 10 && 4 <= ty && ty <= 6)) continue;
      if (check(tx, ty, col)) ++ans;
    }
    return ans;
  }
  i32 calc_xiang(i32 x, i32 y, i32 col) {
    static const i32 dx[] = {2, 2, -2, -2};
    static const i32 dy[] = {2, -2, 2, -2};
    i32 ans = 0;
    for (i32 d = 0; d < 4; ++d) {
      i32 tx = x + dx[d], ty = y + dy[d];
      if (col == 0 && !(1 <= tx && tx <= 5  && 1 <= ty && ty <= 9)) continue;
      if (col == 1 && !(6 <= tx && tx <= 10 && 1 <= ty && ty <= 9)) continue;
      if (s[(x + tx) >> 1][(y + ty) >> 1] == '*' && check(tx, ty, col)) ++ans;
    }
    return ans;
  }
  i32 calc_che(i32 x, i32 y, i32 col) {
    i32 ans = 0;
    for (i32 i = x + 1; i <= 10; ++i) {
      if (s[i][y] == '*') ++ans;
      else {
        if (check(i, y, col)) ++ans;
        break;
      }
    }
    for (i32 i = x - 1; i >= 1; --i) {
      if (s[i][y] == '*') ++ans;
      else {
        if (check(i, y, col)) ++ans;
        break;
      }
    }
    for (i32 i = y + 1; i <= 9; ++i) {
      if (s[x][i] == '*') ++ans;
      else {
        if (check(x, i, col)) ++ans;
        break;
      }
    }
    for (i32 i = y - 1; i >= 1; --i) {
      if (s[x][i] == '*') ++ans;
      else {
        if (check(x, i, col)) ++ans;
        break;
      }
    }
    return ans;
  }
  i32 calc_ma(i32 x, i32 y, i32 col) {
    static const i32 dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    static const i32 dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
    static const i32 fx[] = {1, 1, -1, -1, 0, 0, 0, 0};
    static const i32 fy[] = {0, 0, 0, 0, 1, -1, 1, -1};
    i32 ans = 0;
    for (i32 d = 0; d < 8; ++d) {
      i32 tx = x + dx[d], ty = y + dy[d];
      i32 footx = x + fx[d], footy = y + fy[d];
      if (1 <= tx && tx <= 10 && 1 <= ty && ty <= 9)
        if (check(tx, ty, col) && s[footx][footy] == '*')
          ++ans;
    }
    return ans;
  }
  i32 calc_pao(i32 x, i32 y, i32 col) {
    i32 cnt, ans = 0;
    cnt = 0;
    for (i32 i = x + 1; i <= 10; ++i) {
      if (s[i][y] == '*' && !cnt) ++ans;
      else if (s[i][y] != '*') {
        ++cnt;
        if (cnt == 2 && check(i, y, col)) { ++ans; break; }
      }
    }
    cnt = 0;
    for (i32 i = x - 1; i >= 1; --i) {
      if (s[i][y] == '*' && !cnt) ++ans;
      else if (s[i][y] != '*') {
        ++cnt;
        if (cnt == 2 && check(i, y, col)) { ++ans; break; }
      }
    }
    cnt = 0;
    for (i32 i = y + 1; i <= 9; ++i) {
      if (s[x][i] == '*' && !cnt) ++ans;
      else if (s[x][i] != '*') {
        ++cnt;
        if (cnt == 2 && check(x, i, col)) { ++ans; break; }
      }
    }
    cnt = 0;
    for (i32 i = y - 1; i >= 1; --i) {
      if (s[x][i] == '*' && !cnt) ++ans;
      else if (s[x][i] != '*') {
        ++cnt;
        if (cnt == 2 && check(x, i, col)) { ++ans; break; }
      }
    }
    return ans;
  }
  i32 calc_bing(i32 x, i32 y, i32 col) {
    i32 ans = 0;
    if (col == 0 && x + 1 <= 10 && check(x + 1, y, col)) ++ans;
    if (col == 1 && x - 1 >=  1 && check(x - 1, y, col)) ++ans;
    if ((col == 0 && (6 <= x && x <= 10)) || (col == 1 && (1 <= x && x <= 5))) {
      if (y - 1 >= 1 && check(x, y - 1, col)) ++ans;
      if (y + 1 <= 9 && check(x, y + 1, col)) ++ans;
    }
    return ans;
  }
  void solve() {
    for (i32 i = 1; i <= 10; ++i)
      fscanf(fin, "%s", s[i] + 1);
    i32 ans = 0;
    for (i32 i = 1; i <= 10; ++i)
      for (i32 j = 1; j <= 9; ++j) {
        if (s[i][j] == '*') continue;
        i32 col = ('A' <= s[i][j] && s[i][j] <= 'Z');
        i32 res = 0;
        if (s[i][j] == 'j' || s[i][j] == 'J') res += calc_jiang(i, j, col);
        if (s[i][j] == 's' || s[i][j] == 'S') res += calc_shi(i, j, col);
        if (s[i][j] == 'x' || s[i][j] == 'X') res += calc_xiang(i, j, col);
        if (s[i][j] == 'c' || s[i][j] == 'C') res += calc_che(i, j, col);
        if (s[i][j] == 'm' || s[i][j] == 'M') res += calc_ma(i, j, col);
        if (s[i][j] == 'p' || s[i][j] == 'P') res += calc_pao(i, j, col);
        if (s[i][j] == 'b' || s[i][j] == 'B') res += calc_bing(i, j, col);
        ans += res;
      }
    fprintf(fout, "%d\n", ans);
    return void();
  }
  bool _2;
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("chess.in", "r");
    fout = fopen("chess.out", "w");
    fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
    i32 t = read();
    i64 Start_Time_Without_Read = clock();
    while (t--) solve();
    i64 End_Time_Without_Read = clock();
    fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
    return void();
  }
}
signed main() { return Solution_Of_HLP1471::main(), 0; }