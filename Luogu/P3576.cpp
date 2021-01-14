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

const int MAXN=1e6+5;
const int MAXG=1e6+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,g,k;
int m[MAXG];
int deg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

ll dp[MAXN][2];

inline void dfs(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dp[v][0]=min(inf,dp[u][0]*(deg[u]-1));
			dp[v][1]=min(inf,(dp[u][1]+1)*(deg[u]-1)-1);
			dfs(v,u);
		}
	}
	return;
}

int main(void){
	n=read(),g=read(),k=read();
	for(reg int i=1;i<=g;++i)
		m[i]=read();
	sort(m+1,m+g+1);
	reg int rt1,rt2;
	rt1=read(),rt2=read();
	deg[0]+=2,++deg[rt1],++deg[rt2];
	Add_Edge(0,rt1),Add_Edge(0,rt2);
	for(reg int i=2;i<n;++i){
		static int a,b;
		a=read(),b=read();
		++deg[a],++deg[b];
		Add_Edge(a,b),Add_Edge(b,a);
	}
	dp[0][0]=dp[0][1]=k;
	dfs(0,-1);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		if(deg[i]==1)
			ans+=upper_bound(m+1,m+g+1,dp[i][1])-lower_bound(m+1,m+g+1,dp[i][0]);
	printf("%lld\n",ans*k);
	return 0;
}