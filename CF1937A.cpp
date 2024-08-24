#include <bits/stdc++.h>

using i32 = int32_t;
using i64 = int64_t;

i32 read() {
	i32 x = 0, f = 0; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f |= (ch == '-');
	for (; isdigit(ch); ch = getchar()) x = (x * 10) + (ch - '0');
	return f ? -x : x; 
}

signed main() {
	i32 T = read();
	while (T--) {
		i32 n = read();
		i64 i = 1; 
		while (i * 2 <= n) i *= 2; 
		printf("%lld\n", i); 
	}
	return 0;
}
