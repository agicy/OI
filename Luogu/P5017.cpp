#include <cstdio>
#include <algorithm>
#define INF 0X3F3F3F3F
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++)

static char buf[100000], *p1 = buf, *p2 = buf;
int n, m, t, ans = INF, cnt[4000101], sum[4000101],f[4000101];

inline int read(void){
	register char ch = getchar();
	register int sum = 0;
	while (ch < '0' || ch > '9')
		ch = getchar();
	while ('0' <= ch && ch <= '9')
		sum = (sum << 1) + (sum << 3) + ch - '0',ch = getchar();
	return sum;
}

int main(void){
	register int i, j, ti;
	n = read(), m = read();
	for (i = 1; i <= n; ++i){
		ti = read();
		t = max(t, ti);
		++cnt[ti];
		sum[ti] += ti;
	}
	for (i = 1; i < t + m; ++i)
		cnt[i] += cnt[i - 1],
		sum[i] += sum[i - 1];
	for (i = 1; i < t + m; ++i){
		f[i] = cnt[i] * i - sum[i];
		for (j = max(i - m - m + 1, 0); j <= i - m; ++j){
			f[i] = min(f[i], f[j] + (cnt[i] - cnt[j]) * i - (sum[i] - sum[j]));
		}
	}
	for (i = t; i < t + m; ++i)
		ans = min(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}