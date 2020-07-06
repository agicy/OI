#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100+5;
const int MAXM=500+5;
const int MAXK=11+1;

int n,m,k;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
int p[MAXK];
int dp[MAXN][1<<MAXK];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id,dis;
	inline Node(reg int id=0,reg int dis=0):id(id),dis(dis){
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
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	while (!Q.empty()){
		reg int id=Q.top().id;
		Q.pop();
		if(vis[id])
			continue;
		vis[id]=true;
		for(reg int i=head[id];i;i=Next[i]){
			reg int v=to[i];
			if(dp[v][s]>dp[id][s]+w[i]){
				dp[v][s]=dp[id][s]+w[i];
				Q.push(Node(v,dp[v][s]));
			}
		}
	}
	return;
}

int main(void){
	memset(dp,0X3F,sizeof(dp));
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	for(reg int i=1;i<=k;++i){
		p[i]=read();
		dp[p[i]][1<<(i-1)]=0;
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
	printf("%d\n",dp[p[1]][(1<<k)-1]);
	return 0;
}