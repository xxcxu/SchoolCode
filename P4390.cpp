#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>

using namespace std;

#define int long long

int read(int x = 0, bool f = false, char ch = getchar()) {
	for (; !isdigit(ch); ch = getchar()) f |= (ch == '-');
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return f ? ~x + 1 : x;
}

const int N = 2e5 + 5;

struct p {
	int type, id, x, y;
	friend bool operator < (const p a, const p b) {
		if (a.x != b.x) return a.x < b.x;
		if (a.y != b.y) return a.y < b.y;
		return a.type < b.type;
	}
}query[N], a[N];

int n, m, val, op, tot;
int s[N * 10], ans[N];

#define lowbit(x) ((x)&(-x))

void add(int x, int v) {
	for (; x <= val + 1; x += lowbit(x)) s[x] += v;
}

int ask(int x) {
	int ans = 0;
	for (; x; x -= lowbit(x)) ans += s[x];
	return ans;
}

void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1, tot = 0;
	cdq(l, mid); cdq(mid + 1, r);
	for (int i = l; i <= r; ++i)
		if (i <= mid && !query[i].type) a[++ tot] = query[i];
		else if (i > mid && query[i].type) a[++ tot] = query[i];
	sort(a + 1, a + 1 + tot);
	for (int i = 1; i <= tot; ++i) {
		if (!a[i].type) add(a[i].y, a[i].id);
		else if (a[i].type & 1) ans[a[i].id] += ask(a[i].y);
		else ans[a[i].id] -= ask(a[i].y);
	}
	for (int i = 1; i <= tot; ++i)
		if (!a[i].type) add(a[i].y, -a[i].id);
}

signed main() {
  n = read(), val = read();
	while(1) {
		op = read();
		if (op == 3) break;
		if (op == 1) {
			int x = read(), y = read(), k = read();
			query[++ m] = {0, k, x, y};
		}
		else {
			int x1 = read(), y1 = read(), x2 = read(), y2 = read();
			query[++ m] = {1, ++ tot, x2, y2};
			query[++ m] = {1, tot, x1 - 1, y1 - 1};
			query[++ m] = {2, tot, x1 - 1, y2};
			query[++ m] = {2, tot, x2, y1 - 1};
		}
	}
	cdq(1, m);
	for (int i = 1; i <= tot; ++i) printf("%lld\n", ans[i]);
	return 0;
}