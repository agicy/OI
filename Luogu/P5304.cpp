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
const int MAXM=500000+5;
const int MAXK=MAXN;

int n,m,K;
int id[MAXK];
int cnt,head[MAXN],to[MAXM+MAXK],Next[MAXM+MAXK];
ll w[MAXM+MAXK];

inline void Add_Edge(reg int u,reg int v,reg ll len){
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
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg ll *dis,reg int *color){
	memset(vis,false,sizeof(vis));
	for(reg int i=1;i<=n;++i)dis[i]=INF;
	while(!Q.empty())Q.pop();
	for(reg int i=1;i<=K;++i){
		dis[id[i]]=0;
		color[id[i]]=id[i];
		Q.push(Node(id[i],0));
	}
	while(!Q.empty()){
		reg int ID=Q.top().id;
		Q.pop();
		if(vis[ID])
			continue;
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+w[i]){
				dis[to[i]]=dis[ID]+w[i];
				color[to[i]]=color[ID];
				Q.push(Node(to[i],dis[to[i]]));
			}
	}
	return;
}

int X[MAXM],Y[MAXM],W[MAXM];
ll dis[2][MAXN];
int c[2][MAXN];

inline void Init(void){
	cnt=0;
	memset(head,0,sizeof(head));
	return;
}

inline void Solve(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=m;++i)
		X[i]=read(),Y[i]=read(),W[i]=read();
	for(reg int i=1;i<=K;++i)
		id[i]=read();
	Init();
	for(reg int i=1;i<=m;++i)
		if(X[i]!=Y[i])
			Add_Edge(X[i],Y[i],W[i]);
	Dijkstra(dis[0],c[0]);
	Init();
	for(reg int i=1;i<=m;++i)
		if(X[i]!=Y[i])
			Add_Edge(Y[i],X[i],W[i]);
	Dijkstra(dis[1],c[1]);
	ll ans=INF;
	for(reg int i=1;i<=m;++i){
		reg int x=X[i],y=Y[i],w=W[i];
		if(c[0][x]&&c[1][y]&&c[0][x]!=c[1][y])
			ans=min(ans,dis[0][x]+dis[1][y]+w);
	}
	printf("%lld\n",ans);
	return;
}

int main(void){
	reg int T=read();
	while(T--)
		Solve();
	return 0;
}