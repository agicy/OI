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

const int MAXN=2e5+5;

int n;
int deg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int f[MAXN];

inline int dfs1(reg int u,reg int father){
	reg int p=0;
	f[u]=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			p+=min(w[i],dfs1(v,u));
	}
	if(deg[u]!=1)
		return f[u]=p;
	else
		return w[head[u]];
}

int ans,g[MAXN];

inline void dfs2(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(deg[u]==1)
				g[v]=w[i]+f[v];
			else
				g[v]=f[v]+min(w[i],g[u]-min(w[i],f[v]));
			ans=max(ans,g[v]);
			dfs2(v,u);
		}
	}
	return;
}

int main(void){
	reg int T=read();
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		memset(deg,0,sizeof(deg));
		n=read();
		for(reg int i=1;i<n;++i){
			static int x,y,z;
			x=read(),y=read(),z=read();
			++deg[x],++deg[y];
			Add_Edge(x,y,z),Add_Edge(y,x,z);
		}
		g[1]=dfs1(1,0);
		ans=0;
		dfs2(1,0);
		printf("%d\n",max(g[1],ans));
	}
	return 0;
}