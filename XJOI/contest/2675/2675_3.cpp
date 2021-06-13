#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e3+5;
const int inf=0x3f3f3f3f;

int n;
int c[MAXN],t[MAXN];
vector<int> G[MAXN];
int dis[MAXN][MAXN];

inline void getDis(reg int u,reg int father,reg int rt,reg int dep){
	dis[rt][u]=dep;
	for(int v:G[u])
		if(v!=father)
			getDis(v,u,rt,dep+1);
	return;
}

int f[MAXN][MAXN];
int g[MAXN];

inline void dfs(reg int u,reg int father){
	for(reg int i=1;i<=n;++i)
		f[u][i]=t[dis[u][i]]+c[i];
	for(int v:G[u])
		if(v!=father){
			dfs(v,u);
			for(reg int i=1;i<=n;++i)
				f[u][i]+=min(f[v][i]-c[i],g[v]);
		}
	g[u]=inf;
	for(reg int i=1;i<=n;++i)
		g[u]=min(g[u],f[u][i]);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=n;++i)
		t[i]=read();
	for(reg int i=1;i<n;++i){
		static int s,t;
		s=read(),t=read();
		G[s].push_back(t),G[t].push_back(s);
	}
	for(reg int i=1;i<=n;++i)
		getDis(i,0,i,0);
	dfs(1,0);
	printf("%d\n",g[1]);
	return 0;
}