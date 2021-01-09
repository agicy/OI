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

const int MAXN=5e5+5;

int n,rt;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

ll f[MAXN],g[MAXN];

inline void dfs(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			f[u]=max(f[u],f[v]+w[i]);
			g[u]+=g[v];
		}
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			g[u]+=f[u]-(f[v]+w[i]);
	}
	return;
}

int main(void){
	n=read(),rt=read();
	for(reg int i=1;i<n;++i){
		static int a,b,t;
		a=read(),b=read(),t=read();
		Add_Edge(a,b,t);
		Add_Edge(b,a,t);
	}
	dfs(rt,0);
	printf("%lld\n",g[rt]);
	return 0;
}