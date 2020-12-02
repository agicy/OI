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
const int MAXK=20+5;

int n,k;
int c[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int f[MAXN][MAXK];

inline void dfs(reg int u,reg int father){
	f[u][0]=c[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			for(reg int i=0;i<k;++i)
				f[u][i+1]+=f[v][i];
		}
	}
	return;
}

int g[MAXN][MAXK];
int ans[MAXN];

inline void dp(reg int u,reg int father){
	for(reg int i=0;i<=k;++i)
		ans[u]+=f[u][i]+g[u][i];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			for(reg int i=1;i<=k;++i)
				g[v][i]+=g[u][i-1];
			g[v][1]+=f[u][0];
			for(reg int i=2;i<=k;++i)
				g[v][i]+=f[u][i-1]-f[v][i-2];
			dp(v,u);
		}
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	dfs(1,0);
	dp(1,0);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}