#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=17+5;

int n,m;
bool G[MAXN][MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
ll dp[MAXN][MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz,col[MAXN];

inline void dfs(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	for(reg int i=1;i<=siz;++i){
		dp[u][col[i]]=1;
		for(reg int j=head[u];j;j=Next[j]){
			reg int v=to[j];
			if(v!=father){
				reg ll sum=0;
				for(reg int k=1;k<=siz;++k)
					sum+=dp[v][col[k]]*G[col[i]][col[k]];
				dp[u][col[i]]*=sum;
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u][v]=G[v][u]=true;
	}
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	reg ll ans=0;
	for(reg int S=1;S<(1<<n);++S){
		siz=0;
		for(reg int i=0;i<n;++i)
			if((S>>i)&1)
				col[++siz]=i+1;
		dfs(1,0);
		reg ll res=0;
		for(reg int i=1;i<=siz;++i)
			res+=dp[1][col[i]];
		if((n-__builtin_popcount(S))&1)
			ans-=res;
		else
			ans+=res;
	}
	printf("%lld\n",ans);
	return 0;
}