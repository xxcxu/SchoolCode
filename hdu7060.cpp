#include <bits/stdc++.h>
static const int N = 1e6 + 5;
static const int P = 998244353;
int n, k;
char s[N];
int f[N], g[N], fac[N], inv[N], pow10[N];
int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
int qpow(int x, int y) {
	int ans = 1;
	for (; y; y >>= 1, x = mul(x, x)) if (y & 1) ans = mul(ans, x);
	return ans % P;
}
int binom(int n, int m) {
	if (m < 0 || n < m) return 0;
	return mul(fac[n], mul(inv[m], inv[n - m]));
}
void sieve(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = mul(fac[i - 1], i);
	inv[n] = qpow(fac[n], P - 2);
	for (int i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
	pow10[0] = 1;
	for (int i = 1; i <= n; ++i) pow10[i] = mul(pow10[i - 1], 10);
	return void();
}
void solve() {
	scanf("%d%s", &k, s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) s[i] -= '0';
	f[0] = 1, g[0] = (k > 1);
	for (int i = 1; i <= n; ++i) {
		f[i] = dec(mul(f[i - 1], 2), binom(i - 1, k - 1));
		g[i] = dec(mul(g[i - 1], 2), binom(i - 1, k - 2));
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = inc(ans, mul(f[i - 1], mul(pow10[n - i], s[i])));
	int sum = 0;
	for (int i = n - 1; i >= 1; --i) {
		sum = inc(sum, mul(pow10[n - i - 1], g[i - 1]));
		ans = inc(ans, mul(s[i], sum));
	}
	printf("%d\n", ans);
	return void();
}
signed main() {
	sieve(N - 1);
	int t; scanf("%d", &t);
	while (t--) solve();
	return 0;
}