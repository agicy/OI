#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;
const int MAXE=MAXN*MAXN*2;

int m,n;
int val[MAXN],lvl[MAXN];
int cnt,head[MAXN],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
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

bool vis[MAXN];
int dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline int Dijkstra(reg int s,reg int Min,reg int Max){
	memset(vis,false,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,0));
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
			if(Min<=lvl[v]&&lvl[v]<=Max&&dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	int res=0x3f3f3f3f;
	for(reg int i=1;i<=n;++i)
		res=min(res,val[i]+dis[i]);
	return res;
}

int main(void){
	scanf("%d%d",&m,&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		scanf("%d%d%d",&val[i],&lvl[i],&x);
		for(reg int j=1;j<=x;++j){
			static int t,v;
			scanf("%d%d",&t,&v);
			Add_Edge(i,t,v);
		}
	}
	int ans=0x3f3f3f3f;
	for(reg int i=1;i<=n;++i)
		if(i<=lvl[1]&&lvl[1]<=i+m)
			ans=min(ans,Dijkstra(1,i,i+m));
	printf("%d\n",ans);
	return 0;
}