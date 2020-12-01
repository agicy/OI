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

const int MAXN=2e3+5;
const int MAXK=2e3+5;

int n,k;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int siz[MAXN];
ll dp[MAXN][MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			reg int val=w[i];
			for(reg int i=siz[u];i>=0;--i)
				for(reg int j=siz[v];j>=0;--j){
					ll tmp=dp[u][i]+dp[v][j]+1ll*j*(k-j)*val+1ll*(siz[v]-j)*(n-k+j-siz[v])*val;
					dp[u][i+j]=max(dp[u][i+j],tmp);
				}
			siz[u]+=siz[v];
		}
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	dfs(1,0);
	printf("%lld\n",dp[1][k]);
	return 0;
}