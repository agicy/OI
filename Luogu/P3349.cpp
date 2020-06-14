#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=17+5;

int n,m;
bool vis[MAXN],G[MAXN][MAXN],color[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
ll dp[MAXN][MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID){
	vis[ID]=true;
	for(reg int i=1;i<=n;++i)
		dp[ID][i]=1;
	for(reg int i=head[ID],v=to[i];i;i=Next[i],v=to[i])
		if(!vis[v]){
			DFS(v);
			for(reg int j=1;j<=n;++j){
				reg ll sum=0;
				for(reg int k=1;k<=n;++k)
					sum+=dp[v][k]*(G[k][j]&color[k]&color[j]);
				dp[ID][j]*=sum;
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
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	reg ll ans=0;
	for(reg int S=1;S<(1<<n);++S){
		reg int size=n;
		for(reg int i=1,T=S;i<=n;++i,T>>=1){
			color[i]=(T&1);
			size-=(T&1);
		}
		for(reg int i=1;i<=n;++i)
			vis[i]=false;
		DFS(1);
		reg ll res=0;
		for(reg int i=1;i<=n;++i)
			res+=dp[1][i];
		if(size&1)
			ans-=res;
		else
			ans+=res;
	}
	printf("%lld\n",ans);
	return 0;
}