#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <map>
#include <set>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void read(TAT &a)
{
	static char cc;
	static bool fff;
	while (((cc = getchar()) < '0' || cc > '9') && cc != '-');
	if (cc == '-') fff = 1, a = 0;
	else fff = 0, a = cc - 48;
	while ((cc = getchar()) >= '0' && cc <= '9') a = a * 10 + cc - 48;
	if (fff) a = -a;
}
template <class TAT>
void write(TAT a)
{
	static char cc[25];
	static int ct;
	if (a == 0) {putchar('0'); return;}
	if (a < 0) {putchar('-'); a = -a;}
	ct = 0;
	while (a) {cc[++ct] = a % 10 + 48; a /= 10;}
	while (ct) {putchar(cc[ct--]);}
}
void begin()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
}
void end()
{
	fclose(stdin);
	fclose(stdout);
}
template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

FILE *ans, *src, *ins, *score, *full, *xia;

const int maxn = 1000005;
const int maxe = 1.1e6 + 20;
const int totscore = 10;
const long long Ca[16] = {0, 5652, 303617, 429488, 438417, 8293, 42, 422814142LL, 346, 472167, 183250};

int N, M, P;
int n;
int import[maxn] = {0};
struct edge
{
	int a, b, c;
	edge() {}
	edge(int _a, int _b, int _c):a(_a), b(_b), c(_c) {}
}e[maxn];
int fa[maxn];

void Init()
{
	register int i, j, k;
	fscanf(ins, "%d%d%d", &N, &M, &P);
	for (i = 1; i <= M; ++i)
	{
		fscanf(ins, "%d%d%d", &e[i].a, &e[i].b, &e[i].c);
	}
	for (i = 1; i <= P; ++i)
	{
		fscanf(ins, "%d", &import[i]);
	}
}

int Getfa(int p)
{
	if (fa[p] == p) return p;
	return fa[p] = Getfa(fa[p]);
}

long long Sum = 0;
long long cri = 0;
long long Wc, Ws;

void Calc()
{
	register int i, j, k;
	register int tn = 0;
	fscanf(ans, "%lld%d", &Wc, &tn);
	for (i = 1; i <= tn; ++i)
	{
		fscanf(ans, "%d", &k);
		cri += e[k].c;
	}
}

int Check()
{
	register int i, j, k;
	register int now;
	register int ccc;
	for (i = 1; i <= n; ++i)
	{
		fscanf(src, "%d", &now);
		if (now <= 0 || now > M)
		{
			return 2;
		}
		Sum += e[now].c;
		if (Getfa(e[now].a) != Getfa(e[now].b))
			fa[Getfa(e[now].a)] = Getfa(e[now].b);
	}
	ccc = Getfa(import[1]);
	for (i = 2; i <= P; ++i)
	{
		if (Getfa(import[i]) != ccc)
		{
			return 1;
		}
	}
	return 0;
}

int c[maxe];
bool hash[maxe];
char str[maxe];
bool flag[maxe];
int tot = 0, rem = 0;
long long cnt = 0;
bool sflag = true;
int testcase = 0, sx = 1, sy = 1;
char ss[20] = "build", sur1[20] = ".in", sur2[20] = ".out";
char s1[20], s2[20];
long long fk;


int getid(int x,int y)
{
	return (x - 1) * M + y;
}
int getx(int id)
{
	return (id - 1) / M + 1;
}
int gety(int id)
{
	return id % M == 0 ? M : id % M;
}
void dfs(int x,int y)
{
	if(hash[getid(x, y)]) return;
	hash[getid(x, y)] = true;
	if(c[getid(x, y)] == 0) rem++;
	if(x > 1 && flag[getid(x - 1, y)]) dfs(x - 1, y);
	if(x < N && flag[getid(x + 1, y)]) dfs(x + 1, y);
	if(y > 1 && flag[getid(x, y - 1)]) dfs(x, y - 1);
	if(y < M && flag[getid(x, y + 1)]) dfs(x, y + 1);
}

string pstr[7];
string pig("build");

int main(int ppp, char *ccc[])
{
	if (ppp <= 1)
	{
		puts("[usage]:checker l | [l:the number of testcase]");
		return 0;
	}
	pstr[1] = pig + ccc[1] + ".in";
	pstr[2] = pig + ccc[1] + ".out";
	ins = fopen(pstr[1].c_str(), "r");
	src = fopen(pstr[2].c_str(), "r");
	score = stderr;
	xia = stderr;
	if (ccc[1][1] == '0') testcase = 10;
	else testcase = ccc[1][0] - '0';
	fprintf(stderr, "your score is ");
	if (testcase <= 5)
	{
		Init();
		if (fscanf(src, "%lld%d", &Ws, &n) == 0)
		{
			fprintf(score, "0\n");
			fprintf(xia, "ETO is not here!");
			return 0;
		}
		if (n >= M)
		{
			fprintf(score, "0\n");
			fprintf(xia, "ETO is invalid!");
		}
		for (int i = 1; i <= N; ++i) fa[i] = i;
		int tmp = Check();
		if (tmp != 0)
		{
			if (tmp == 1)
			{
				fprintf(score, "0\n");
				fprintf(xia, "ETO is schismatical!");
			}
			else if (tmp == 2)
			{
				fprintf(score, "0\n");
				fprintf(xia, "ETO is invalid!");
			}
			return 0;
		}
		cri = Ca[testcase];
		fprintf(score, "%d\n", min(12, (int)(10 * (Sum / cri))));
		fprintf(xia, "ETO is great!");
	}
	else
	{
		fscanf(ins, "%d%d", &N, &M);
		for(int i = 1, t; i <= N; i++)
			for(int j = 1; j <= M; j++)
			{
				fscanf(ins, "%d", &t);
				c[getid(i, j)] = t;
				if(!t) sx = i, sy = j, tot++;
			}
		if (fscanf(src, "%lld", &fk) != 1)
		{
			fprintf(score, "0\n");
			fprintf(xia, "ETO is not here!");
			return 0;
		}
		for(int i = 1; i <= N; i++)
		{
			fscanf(src, "%s", str + 1);
			if (strlen(str + 1) > M)
			{
				fprintf(score, "0\n");
				fprintf(xia, "ETO is invalid!");
				return 0;
			}
			for(int j = 1; j <= M; j++)
				if(str[j] != 'X')
				{
					flag[getid(i, j)] = true;
					cnt += c[getid(i, j)];
				}
		}
		dfs(sx, sy);
		if (tot != rem)
		{
			fprintf(score, "0\n");
			fprintf(xia, "ETO is schismatical!");
		}
		else
		{
			fprintf(score, "%d\n", min((int)floor(((double) Ca[testcase] / cnt + 0.00001) * totscore), 12));
			fprintf(xia, "ETO is great!");
			return 0;
		}
	}
	return 0;
}
