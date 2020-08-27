#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=5e4+5;
const int MAXM=1e5+5;

int n,m;
int a[6];
int d[6][6];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

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

inline void Dijkstra(reg int s){
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
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return;
}

bool _vis[7];
int p[7];
ll ans=0x3f3f3f3f3f3f3f3fll;

inline void dfs(reg int dep){
	if(dep>5){
		ll sum=0;
		for(reg int i=0;i<5;++i)
			sum+=d[p[i]][p[i+1]];
		ans=min(ans,sum);
		return;
	}
	for(reg int i=0;i<6;++i)
		if(!_vis[i]){
			_vis[i]=true;
			p[dep]=i;
			dfs(dep+1);
			_vis[i]=false;
		}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	a[0]=1;
	for(reg int i=1;i<=5;++i)
		scanf("%d",&a[i]);
	for(reg int i=1;i<=m;++i){
		static int x,y,t;
		scanf("%d%d%d",&x,&y,&t);
		Add_Edge(x,y,t);
		Add_Edge(y,x,t);
	}
	for(reg int i=0;i<6;++i){
		Dijkstra(a[i]);
		for(reg int j=0;j<6;++j)
			d[i][j]=dis[a[j]];
	}
	p[0]=0,_vis[0]=true;
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}