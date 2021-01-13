#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

int n,q;
int deg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int f[MAXN];

inline void dfs1(reg int u,reg int father){
	f[u]=deg[u];
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			f[u]=add(f[u],f[v]);
		}
	}
	return;
}

int g[MAXN];
int sumf[MAXN],sumg[MAXN];

inline void dfs2(reg int u,reg int father){
	reg int sum=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			sum=add(sum,f[v]);
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			g[v]=add(add(deg[u],g[u]),add(sum,p-f[v]));
			sumf[v]=add(sumf[u],f[v]);
			sumg[v]=add(sumg[u],g[v]);
			dfs2(v,u);
		}
	}
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int query(reg int x,reg int y){
	reg int lca=LCA(x,y);
	return add(add(sumf[x],p-sumf[lca]),add(sumg[y],p-sumg[lca]));
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		++deg[u],++deg[v];
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0),dfs2(1,0);
	while(q--){
		static int x,y;
		x=read(),y=read();
		printf("%d\n",query(x,y));
	}
	return 0;
}