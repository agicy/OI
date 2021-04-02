#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

inline double min(reg double a,reg double b){
	return a<b?a:b;
}

const int MAXN=2e3+5;
const int MAXM=2e3+5;
const int MAXV=300+5;
const int MAXE=9e4+5;
const int inf=0x3f3f3f3f;

int n,m,v,e;
int c[MAXN],d[MAXN];
double k[MAXN];
int cnt,head[MAXV],to[MAXE<<1],w[MAXE<<1],Next[MAXE<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

int dis[MAXN][MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(reg int s,reg int dis[]){
	static bool vis[MAXN];
	memset(vis,false,sizeof(vis));
	fill(dis+1,dis+v+1,inf);
	dis[s]=0,Q.push(Node(s,dis[s]));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

double dp[MAXN][MAXM][2];

int main(void){
	n=read(),m=read(),v=read(),e=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=n;++i)
		d[i]=read();
	for(reg int i=1;i<=n;++i)
		scanf("%lf",&k[i]);
	for(reg int i=1;i<=e;++i){
		static int a,b,w;
		a=read(),b=read(),w=read();
		Add_Edge(a,b,w),Add_Edge(b,a,w);
	}
	for(reg int i=1;i<=v;++i)
		dijkstra(i,dis[i]);
	for(reg int i=1;i<=n;++i)
		for(reg int j=0;j<=m;++j)
			dp[i][j][0]=dp[i][j][1]=inf;
	dp[1][0][0]=dp[1][1][1]=0;
	for(reg int i=2;i<=n;++i)
		for(reg int j=0;j<=min(m,i);++j){
			dp[i][j][0]=min(dp[i-1][j][0]+dis[c[i-1]][c[i]],dp[i-1][j][1]+dis[d[i-1]][c[i]]*k[i-1]+dis[c[i-1]][c[i]]*(1-k[i-1]));
			if(j)
				dp[i][j][1]=min(dp[i-1][j-1][0]+dis[c[i-1]][d[i]]*k[i]+dis[c[i-1]][c[i]]*(1-k[i]),dp[i-1][j-1][1]+dis[c[i-1]][c[i]]*(1-k[i-1])*(1-k[i])+dis[c[i-1]][d[i]]*(1-k[i-1])*k[i]+dis[d[i-1]][c[i]]*(1-k[i])*k[i-1]+dis[d[i-1]][d[i]]*k[i-1]*k[i]);
		}
	reg double ans=inf;
	for(reg int i=0;i<=m;++i)
		ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
	printf("%.2lf\n",ans);
	return 0;
}