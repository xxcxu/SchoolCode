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
namespace Solution_Of_P4103 {
	bool _1;
	static const i32 N = 1000005;
	static const i32 inf32 = 0x3f3f3f3f;
	i32 n, m, k;
	i64 ans1; i32 ans2, ans3;
	i32 dfn[N], dep[N], size[N], f[N], g[N];
	i32 anc[N][20];
	bool spc[N];
	std::vector<i32> e[N], gr[N];
	bool _2;
	void dfs(i32 x, i32 fa) {
		static i32 ts = 0;
		dep[x] = dep[fa] + 1;
		dfn[x] = ++ts;
		anc[x][0] = fa;
		for (i32 i = 1; i < 20; ++i) anc[x][i] = anc[anc[x][i - 1]][i - 1];
		for (i32 y : e[x]) if (y != fa) dfs(y, x);
		return void();
	}
	i32 lca(i32 x, i32 y) {
		if (dep[x] < dep[y]) std::swap(x, y);
		for (i32 i = 19; i >= 0; --i)
			if (dep[anc[x][i]] >= dep[y])
				x = anc[x][i];
		if (x == y) return x;
		for (i32 i = 19; i >= 0; --i)
			if (anc[x][i] != anc[y][i])
				x = anc[x][i], y  = anc[y][i];
		return anc[x][0];
	}
	void dfs(i32 x) {
		size[x] = 0, f[x] = -inf32, g[x] = inf32;
		if (spc[x]) size[x] = 1, f[x] = 0, g[x] = 0;
		for (i32 y : gr[x]) {
			dfs(y);
			ans1 += 1LL * (dep[y] - dep[x]) * size[y] * (k - size[y]);
			ans2 = std::min(ans2, g[x] + g[y] + (dep[y] - dep[x]));
			ans3 = std::max(ans3, f[x] + f[y] + (dep[y] - dep[x]));
			g[x] = std::min(g[x], g[y] + (dep[y] - dep[x]));
			f[x] = std::max(f[x], f[y] + (dep[y] - dep[x]));
			size[x] += size[y];
		}
		return void();
	}
	void main() {
		fin = stdin, fout = stdout, ferr = stderr;
		fprintf(ferr, "This code use %.2lf MB memory\n", 1.0 * (&_1 - &_2) / 1024 / 1024);
		n = read();
		for (i32 i = 1; i < n; ++i) {
			static i32 u, v;
			u = read(), v = read();
			e[u].eb(v), e[v].eb(u);
		}
		dfs(1, 0);
		i64 Start_Time_Without_Read = clock();
		m = read();
		while (m--) {
			std::vector<i32> node;
			k = read();
			for (i32 i = 0; i < k; ++i) node.eb(read());
			for (i32 i : node) spc[i] = true;
			std::sort(all(node), [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
			for (i32 i = 1; i < k; ++i) node.eb(lca(node[i - 1], node[i]));
			std::sort(all(node), [&](const i32 &x, const i32 &y) { return dfn[x] < dfn[y]; });
			node.erase(std::unique(all(node)), node.end());
			for (i32 i : node) gr[i].clear();
			for (i32 i = 1; i < std::size(node); ++i) gr[lca(node[i - 1], node[i])].eb(node[i]);
			ans1 = 0, ans2 = inf32, ans3 = -inf32;
			dfs(node[0]);
			fprintf(fout, "%lld %d %d\n", ans1, ans2, ans3);
			for (i32 i : node) spc[i] = false;
		}
		i64 End_Time_Without_Read = clock();
		fprintf(ferr, "This code use %lld ms time\n", End_Time_Without_Read - Start_Time_Without_Read);
		return void();
	}
}
signed main() { return Solution_Of_P4103::main(), 0; }