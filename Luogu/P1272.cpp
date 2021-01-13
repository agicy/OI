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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=150+5;
const int MAXP=150+5;

int n,p;
int outdeg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int dp[MAXN][MAXP];

inline void dfs(reg int u){
	siz[u]=1;
	dp[u][1]=outdeg[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
		siz[u]+=siz[v];
		for(reg int j=min(siz[u],p);j>=1;--j)
			for(reg int k=1;k<j;++k)
				dp[u][j]=min(dp[u][j],dp[u][j-k]+dp[v][k]-1);
	}
	return;
}

int main(void){
	n=read(),p=read();
	for(reg int i=1;i<n;++i){
		static int I,J;
		I=read(),J=read();
		Add_Edge(I,J);
		++outdeg[I];
	}
	memset(dp,0x3f,sizeof(dp));
	dfs(1);
	reg int ans=dp[1][p];
	for(reg int i=2;i<=n;++i)
		ans=min(ans,dp[i][p]+1);
	printf("%d\n",ans);
	return 0;
}