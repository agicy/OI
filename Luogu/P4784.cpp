#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int MAXM=200000+5;
const int MAXK=5+1;

int n,m,k;
int p[MAXK];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id;
	ll dis;
	inline Node(reg int id=0,reg ll dis=0):id(id),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXN];
ll dp[MAXN][1<<MAXK];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int S){
	memset(vis,false,sizeof(vis));
	while(!Q.empty()){
		reg int id=Q.top().id;
		Q.pop();
		if(vis[id])
			continue;
		vis[id]=true;
		for(reg int i=head[id];i;i=Next[i]){
			reg int v=to[i];
			if(dp[v][S]>dp[id][S]+w[i]){
				dp[v][S]=dp[id][S]+w[i];
				Q.push(Node(v,dp[v][S]));
			}
		}
	}
	return;
}

int main(void){
	memset(dp,0X3F,sizeof(dp));
	n=read(),k=read(),m=read();
	for(reg int i=1;i<=k;++i){
		p[i]=read();
		dp[p[i]][1<<(i-1)]=0;
	}
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Edge(a,b,c);
		Add_Edge(b,a,c);
	}
	for(reg int S=1;S<(1<<k);++S){
		for(reg int i=1;i<=n;++i){
			for(reg int sub=S&(S-1);sub;sub=S&(sub-1))
				dp[i][S]=min(dp[i][S],dp[i][sub]+dp[i][S^sub]);
			if(dp[i][S]!=INF)
				Q.push(Node(i,dp[i][S]));
		}
		Dijkstra(S);
	}
	ll ans=INF;
	for(reg int i=1;i<=n;++i)
		ans=min(ans,dp[i][(1<<k)-1]);
	printf("%lld\n",ans);
	return 0;
}