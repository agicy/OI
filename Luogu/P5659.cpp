#include <bits/stdc++.h>
using namespace std;

inline int gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

const int maxn = 2005;

inline void chkmin(int &a, int b) {if (a > b) a = b;}

int n, nump[maxn];

struct edge
{
	int to, next;
} e[maxn * 2];
int h[maxn], tot;

struct node
{
	int fst, lst, cnt, fa[maxn];
	bool bg[maxn], ed[maxn];

	void clear() {fst = lst = cnt = 0; for (int i = 1; i <= n; ++i) fa[i] = i, bg[i] = ed[i] = 1;}
	int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
} t[maxn];

inline void add(int u, int v)
{
	e[++tot] = (edge) {v, h[u]}; h[u] = tot; ++t[u].cnt;
	e[++tot] = (edge) {u, h[v]}; h[v] = tot; ++t[v].cnt;
}

int dfs1(int u, int fe)
{
	int res = n + 1;
	if (fe && (!t[u].lst || t[u].lst == fe)) {
		if (t[u].ed[fe] && !(t[u].fst && t[u].cnt > 1 && t[u].find(fe) == t[u].find(t[u].fst)))
			res = u;
	}
	for (int i = h[u], v, te; v = e[i].to, i; i = e[i].next) {
		if (fe == (te = (i >> 1))) continue;
		te = i >> 1;
		if (!fe) {
			if (!t[u].fst || t[u].fst == te) {
				if (!t[u].bg[te]) continue;
				if (t[u].lst && t[u].cnt > 1 && t[u].find(te) == t[u].find(t[u].lst)) continue;
				chkmin(res, dfs1(v, te));
			} else continue;
		} else {
			if (fe == t[u].lst || te == t[u].fst || t[u].find(fe) == t[u].find(te)) continue;
			if (!t[u].ed[fe] || !t[u].bg[te]) continue;
			if (t[u].fst && t[u].lst && t[u].cnt > 2 && t[u].find(fe) == t[u].find(t[u].fst) && t[u].find(te) == t[u].find(t[u].lst)) continue;

			chkmin(res, dfs1(v, te));
		}
	}
	return res;
}

int dfs2(int u, int fe, int p)
{
	if (u == p) return t[u].lst = fe, 1;
	for (int i = h[u], v, te; v = e[i].to, i; i = e[i].next)
		if (fe != (te = (i >> 1)))
			if (dfs2(v, te, p)) {
				if (!fe) t[u].fst = te;
				else {
					t[u].ed[fe] = t[u].bg[te] = 0; --t[u].cnt;
					t[u].fa[t[u].find(fe)] = t[u].find(te);
				}
				return 1;
			}
	return 0;
}

int main()
{
	int T = gi();
	while (T--) {
		tot = 1;
		memset(h + 1, 0, sizeof(int) * n);

		n = gi();
		for (int i = 1; i <= n; ++i) t[i].clear();
		for (int i = 1; i <= n; ++i) nump[i] = gi();
		for (int i = 1; i < n; ++i) add(gi(), gi());

		if (n == 1) {puts("1"); continue;}

		for (int p, i = 1; i <= n; ++i) {
			p = dfs1(nump[i], 0);
			dfs2(nump[i], 0, p);
			printf("%d ", p);
		}
		puts("");
	}

	return 0;
}