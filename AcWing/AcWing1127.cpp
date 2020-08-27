#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int MAXP=800+5;
const int MAXC=1450+5;

int n,p,c;
int id[MAXN];
int cnt,head[MAXP],to[MAXC<<1],Next[MAXC<<1];
ll w[MAXC<<1];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id;
	ll val;
	inline Node(reg int id=0,reg ll val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

const int inf=0x3f3f3f3f;

bool vis[MAXP];
ll dis[MAXP];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	for(reg int i=1;i<=p;++i)
		dis[i]=inf;
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
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

int main(void){
	scanf("%d%d%d",&n,&p,&c);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&id[i]);
	for(reg int i=1;i<=c;++i){
		static int a,b;
		static ll d;
		scanf("%d%d%lld",&a,&b,&d);
		Add_Edge(a,b,d);
		Add_Edge(b,a,d);
	}
	ll ans=0x3f3f3f3f3f3f3f3fll;
	for(reg int i=1;i<=p;++i){
		Dijkstra(i);
		ll sum=0;
		for(reg int j=1;j<=n;++j)
			sum+=dis[id[j]];
		ans=min(ans,sum);
	}
	printf("%lld\n",ans);
	return 0;
}