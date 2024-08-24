#include <bits/stdc++.h>

using i32 = int32_t;
using i64 = int64_t;

i32 read() {
	i32 x = 0, f = 0; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f |= (ch == '-');
	for (; isdigit(ch); ch = getchar()) x = (x * 10) + (ch - '0');
	return f ? -x : x; 
}

static const i32 N = 200005;

i32 n, a[2][N], b[N], dp[N][2];
char s[N];

void solve() {
	n = read();
	scanf("%s", s + 1);
	for (i32 i = 1; i <= n; ++i) a[0][i] = s[i] - '0';
	scanf("%s", s + 1);
	for (i32 i = 1; i <= n; ++i) a[1][i] = s[i] - '0';
	for (i32 i = 1, nx = 1, ny = 0; i <= n; ++i) {
		b[i] = a[ny][nx];
		i32 tx1 = nx, ty1 = ny + 1;
		i32 tx2 = nx + 1, ty2 = ny;
		if (tx2 > n) { nx = tx1, ny = ty1; continue; }
		if (ty1 > 1) { nx = tx2, ny = ty2; continue; }
		i32 t1 = a[ty1][tx1], t2 = a[ty2][tx2];
		if (t1 < t2) { nx = tx1, ny = ty1; continue; }
		if (t1 > t2) { nx = tx2, ny = ty2; continue; }
		nx = tx2, ny = ty2;
	}
	b[n + 1] = a[1][n];
	dp[1][0] = 1;
	for (i32 i = 1; i <= n; ++i)
		for (i32 j = 0; j < 2; ++j)	
			if (i != 1 || j != 0) {
				dp[i][j] = 0;
				if (a[j][i] == b[i + j]) {
					if (i > 1) dp[i][j] += dp[i - 1][j];
					if (j > 0) dp[i][j] += dp[i][j - 1];
				}
			}
//		puts(".......");
//		for (i32 i = 1; i <= n; ++i) printf("%d ", dp[i][0]);
//		puts("");
//		for (i32 i = 1; i <= n; ++i) printf("%d ", dp[i][1]);
//		puts("");
//		puts(".......");
	for (i32 i = 1; i <= n + 1; ++i) printf("%d", b[i]);
	puts("");
	printf("%d\n", dp[n][1]);
	return void();
}

signed main() {
	i32 t = read();
	while (t--) solve();
	return 0;
}
