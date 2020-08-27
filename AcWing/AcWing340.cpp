#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const int MAXP=1e4+5;
const int MAXK=1e3+5;

int n,p,k;
int cnt,head[MAXN],to[MAXP<<1],Next[MAXP<<1];
ll w[MAXP<<1];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int dep,id;
	ll val;
	inline Node(reg int dep=0,reg int id=0,reg ll val=0):dep(dep),id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

bool vis[MAXK][MAXN];
ll dis[MAXK][MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[0][s]=0,Q.push(Node(0,s,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id,dep=s.dep;
		if(vis[dep][u])
			continue;
		vis[dep][u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep<k&&dis[dep+1][v]>dis[dep][u]){
				dis[dep+1][v]=dis[dep][u];
				Q.push(Node(dep+1,v,dis[dep+1][v]));
			}
			if(dis[dep][v]>max(dis[dep][u],w[i])){
				dis[dep][v]=max(dis[dep][u],w[i]);
				Q.push(Node(dep,v,dis[dep][v]));
			}
		}
	}
	return;
}

const ll inf=0x3f3f3f3f3f3f3f3fll;

int main(void){
	scanf("%d%d%d",&n,&p,&k);
	for(reg int i=1;i<=p;++i){
		static int a,b;
		static ll l;
		scanf("%d%d%lld",&a,&b,&l);
		Add_Edge(a,b,l);
		Add_Edge(b,a,l);
	}
	Dijkstra(1);
	ll ans=inf;
	for(reg int i=0;i<=k;++i)
		ans=min(ans,dis[i][n]);
	if(ans==inf)
		puts("-1");
	else
		printf("%lld\n",ans);
	return 0;
}