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

int n;
int c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int sum,siz[MAXN];
ll ans=1e18,f[MAXN];

inline void dfs1(reg int u,reg int father,reg int dis){
	siz[u]=c[u];
	f[1]+=1ll*dis*c[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u,dis+w[i]);
			siz[u]+=siz[v];
		}
	}
	return;
}

inline void dfs2(reg int u,reg int father){
	ans=min(ans,f[u]);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			f[v]=f[u]-1ll*siz[v]*w[i]+1ll*(sum-siz[v])*w[i];
			dfs2(v,u);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		c[i]=read();
		sum+=c[i];
	}
	for(reg int i=1;i<n;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		Add_Edge(a,b,l);
		Add_Edge(b,a,l);
	}
	dfs1(1,0,0);
	dfs2(1,0);
	printf("%lld\n",ans);
	return 0;
}