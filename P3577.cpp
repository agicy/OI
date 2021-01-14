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

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e4+5;
const int MAXM=2.5e4+5;
const int inf=0x3f3f3f3f;
const int basep[]={1,3,9,27,81,243,729,2187,6561,19683,59049};

int n,m;
int c[MAXN];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int dep[MAXN];
int dp[10][59049];
int bit[59049][10];

inline int getBit(reg int S,reg int i){
	return bit[S][i];
}

inline void dfs(reg int u){
	vis[u]=true;
	reg int tot=0;
	static int Q[MAXN];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(vis[v]&&dep[v]<dep[u])
			Q[++tot]=v;
	}
	if(!dep[u])
		dp[0][0]=c[u],dp[0][1]=0,dp[0][2]=inf;
	else{
		for(reg int i=basep[dep[u]+1]-1;i>=0;--i)
			dp[dep[u]][i]=inf;
		for(reg int i=0;i<basep[dep[u]];++i){
			reg int No=1,Yes=i;
			for(reg int j=1;j<=tot;++j){
				if(!getBit(i,dep[Q[j]]))
					No=2;
				if(getBit(i,dep[Q[j]])==1)
					Yes+=basep[dep[Q[j]]];
			}
			cMin(dp[dep[u]][i+No*basep[dep[u]]],dp[dep[u]-1][i]);
			cMin(dp[dep[u]][Yes],dp[dep[u]-1][i]+c[u]);
		}
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			dep[v]=dep[u]+1;
			dfs(v);
			for(reg int j=0;j<basep[dep[v]];++j)
				dp[dep[u]][j]=min(dp[dep[v]][j],dp[dep[v]][j+2*basep[dep[v]]]);
		}
	}
	return;
}

int main(void){
	for(reg int i=0;i<59049;++i){
		reg int tmp=i,cnt=0;
		while(tmp){
			bit[i][cnt++]=tmp%3;
			tmp/=3;
		}
	}
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(!vis[i]){
			dfs(i);
			ans+=min(dp[0][0],dp[0][2]);
		}
	printf("%d\n",ans);
	return 0;
}